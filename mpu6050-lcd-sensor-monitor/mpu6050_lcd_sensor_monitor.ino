#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const int potentiometer_pin = 34;
const int sda_pin = 26;
const int scl_pin = 25;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin(sda_pin, scl_pin);

  lcd.init();
  lcd.backlight();
  lcd.print("Initializing...");

  if (!mpu.begin(0x68)) {
    lcd.clear();
    lcd.print("MPU6050 error");
    Serial.println("MPU6050 not found. Check wiring and I2C address.");
    while (true) delay(100);
  }

  pinMode(potentiometer_pin, INPUT);
  delay(1000);
  lcd.clear();
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);
  int pot_reading = analogRead(potentiometer_pin);

  lcd.setCursor(0, 0);
  lcd.print("Pot:");
  lcd.print(pot_reading);
  lcd.print("       ");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temp.temperature, 1);
  lcd.print(" C   ");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ax:"); lcd.print(accel.acceleration.x, 1);
  lcd.print(" Ay:"); lcd.print(accel.acceleration.y, 1);
  lcd.setCursor(0, 1);
  lcd.print("Az:"); lcd.print(accel.acceleration.z, 1);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gx:"); lcd.print(gyro.gyro.x, 1);
  lcd.print(" Gy:"); lcd.print(gyro.gyro.y, 1);
  lcd.setCursor(0, 1);
  lcd.print("Gz:"); lcd.print(gyro.gyro.z, 1);
  delay(3000);
  lcd.clear();
}
