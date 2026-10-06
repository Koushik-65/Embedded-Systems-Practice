#include "secrets.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Pins
#define TRIG_PIN 13
#define ECHO_PIN 15
#define PIR_PIN 5
#define LED_PIN 4

// Sensor objects
Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool mpuAvailable = false;

// Data sent from the MPU task to the alert task
struct MPUData {
  float accelX;
  float accelY;
  float accelZ;

  float gyroX;
  float gyroY;
  float gyroZ;

  float temperature;
};

// Current system state sent to the Blynk dashboard
struct NetworkPacket {
  bool systemState;
  bool buzzerState;
  bool ledState;
  bool intrusionState;
};

// FreeRTOS queues
// Queue length is 1 because only the latest sensor/system state is needed.
QueueHandle_t ultrasonicQueue;
QueueHandle_t pirQueue;
QueueHandle_t mpuQueue;
QueueHandle_t displayQueue;
QueueHandle_t networkTxQueue;
QueueHandle_t networkRxQueue;

// Packet sent from AlertTask to NetworkTask
NetworkPacket TxPacket;

// V0 controls whether the security system is armed or disarmed.
BLYNK_WRITE(V0) {
  bool armed = param.asInt();
  xQueueOverwrite(networkRxQueue, &armed);
}

void pirTask(void *parameter) {
  int state = LOW;

  while (true) {
    int motionDetected = digitalRead(PIR_PIN);

    if (motionDetected) {
      state = HIGH;
    }
    else {
      state = LOW;
    }

    xQueueOverwrite(pirQueue, &state);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void ultrasonicTask(void *parameter) {
  while (true) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    // Timeout prevents this task from waiting indefinitely if no echo returns.
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration > 0) {
      int distance = duration * 0.0343 / 2.0;
      xQueueOverwrite(ultrasonicQueue, &distance);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void MPUTask(void *parameter) {
  while (true) {
    sensors_event_t acceleration;
    sensors_event_t gyro;
    sensors_event_t temperature;

    mpu.getEvent(&acceleration, &gyro, &temperature);

    MPUData mpuData;

    mpuData.accelX = acceleration.acceleration.x;
    mpuData.accelY = acceleration.acceleration.y;
    mpuData.accelZ = acceleration.acceleration.z;

    mpuData.gyroX = gyro.gyro.x;
    mpuData.gyroY = gyro.gyro.y;
    mpuData.gyroZ = gyro.gyro.z;

    mpuData.temperature = temperature.temperature;

    xQueueOverwrite(mpuQueue, &mpuData);
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

// Receives the latest sensor data and decides whether an intrusion is active.
void AlertTask(void *parameter) {
  int receivedDistance = 999;
  int receivedPIRState = LOW;

  MPUData receivedMPUData = {};

  bool mpuDataReceived = false;
  bool receivedSystemState;
  bool previousIntrusionState = false;

  while (true) {
    bool intrusion = false;

    xQueueReceive(ultrasonicQueue, &receivedDistance, 0);
    xQueueReceive(pirQueue, &receivedPIRState, 0);

    if (
      mpuAvailable &&
      xQueueReceive(mpuQueue, &receivedMPUData, 0) == pdTRUE
    ) {
      mpuDataReceived = true;
    }

    float magnitude = sqrt(
      receivedMPUData.accelX * receivedMPUData.accelX +
      receivedMPUData.accelY * receivedMPUData.accelY +
      receivedMPUData.accelZ * receivedMPUData.accelZ
    );

    // Detect sudden movement of the device.
    if (mpuDataReceived && fabs(magnitude - 9.81) > 3.0) {
      intrusion = true;
    }

    // Detect nearby objects or PIR motion.
    if (receivedDistance < 20 || receivedPIRState == HIGH) {
      intrusion = true;
    }

    // Receive ARM / DISARM state from Blynk.
    if (
      xQueueReceive(networkRxQueue, &receivedSystemState, 0) == pdTRUE
    ) {
      TxPacket.systemState = receivedSystemState;
    }

    // Alarm outputs only activate while the system is armed.
    if (intrusion && TxPacket.systemState) {
      digitalWrite(LED_PIN, HIGH);

      TxPacket.ledState = true;
      TxPacket.intrusionState = true;
      TxPacket.buzzerState = true;
    }
    else {
      digitalWrite(LED_PIN, LOW);

      TxPacket.ledState = false;
      TxPacket.intrusionState = false;
      TxPacket.buzzerState = false;
    }

    // Only update Blynk when intrusion state changes to save messages.
    if (TxPacket.intrusionState != previousIntrusionState) {
      xQueueOverwrite(networkTxQueue, &TxPacket);
    }

    xQueueOverwrite(displayQueue, &TxPacket.intrusionState);

    previousIntrusionState = TxPacket.intrusionState;
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void lcdTask(void *parameter) {
  bool intrusion = false;
  bool previousState = false;

  while (true) {
    if (xQueueReceive(displayQueue, &intrusion, 0) == pdTRUE) {
      // Only rewrite the LCD when the displayed state changes.
      if (intrusion != previousState) {
        lcd.clear();

        if (intrusion) {
          lcd.setCursor(0, 0);
          lcd.print("Intruder ALERT!");

          lcd.setCursor(0, 1);
          lcd.print("Check System");
        }

        previousState = intrusion;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

// Handles communication between the ESP32 and Blynk.
void NetworkTask(void *parameter) {
  while (true) {
    if (WiFi.status() == WL_CONNECTED) {
      Blynk.run();

      if (xQueueReceive(networkTxQueue, &TxPacket, 0) == pdTRUE) {
        Blynk.virtualWrite(V1, TxPacket.buzzerState);
        Blynk.virtualWrite(V2, TxPacket.ledState);
        Blynk.virtualWrite(V3, TxPacket.intrusionState);
      }
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void setup() {
  Serial.begin(115200);

  // GPIO setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  // I2C setup
  Wire.begin(32, 33); // SDA, SCL
  Wire.setClock(100000);

  // MPU setup
  if (mpu.begin(0x68, &Wire)) {
    mpuAvailable = true;
    Serial.println("MPU initialized");
  }
  else {
    mpuAvailable = false;
    Serial.println("MPU initialization failed");
  }

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Queue setup
  ultrasonicQueue = xQueueCreate(1, sizeof(int));
  pirQueue = xQueueCreate(1, sizeof(int));
  mpuQueue = xQueueCreate(1, sizeof(MPUData));
  displayQueue = xQueueCreate(1, sizeof(bool));
  networkTxQueue = xQueueCreate(1, sizeof(NetworkPacket));
  networkRxQueue = xQueueCreate(1, sizeof(bool));

  // WiFi setup
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting...");
  }

  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());

  // Blynk setup
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();

  // Create FreeRTOS tasks
  xTaskCreate(
    ultrasonicTask,
    "Ultrasonic Task",
    2048,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    pirTask,
    "PIR Task",
    1024,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    lcdTask,
    "LCD Task",
    2048,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    AlertTask,
    "Alert Task",
    2048,
    NULL,
    2,
    NULL
  );

  // Do not run the MPU task if sensor initialization failed.
  if (mpuAvailable) {
    xTaskCreate(
      MPUTask,
      "MPU Task",
      2048,
      NULL,
      2,
      NULL
    );
  }

  xTaskCreate(
    NetworkTask,
    "Network Task",
    4096,
    NULL,
    1,
    NULL
  );
}

// All application logic runs inside FreeRTOS tasks.
void loop() {
}
