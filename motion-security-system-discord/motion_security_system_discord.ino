#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>
#include <string>

//we are going to use State-Change detection in here.
/*   Arm/Disarm Button  */

//Settings
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* webhook_URL = "YOUR_DISCORD_WEBHOOK_URL";

//PINS
const int PIR_pin = 23;
const int Buzzer_pin = 4;
const int activation_pin = 19;

//OBJECTS
HTTPClient http;
bool last_state = false;

void setup() {

  Serial.begin(115200);
  pinMode(PIR_pin, INPUT);
  pinMode(Buzzer_pin, OUTPUT);
  pinMode(activation_pin, INPUT_PULLUP);

  //Wi-Fi Setup

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
  }

  Serial.println("Wi-Fi Connected.");

  //Webhook Setup

  http.begin(webhook_URL);
  http.addHeader("Content-Type", "application/JSON");

  int responsecode = http.POST("{\"content\" : \"Connected.\"}");

  Serial.print("Discord Response Code: ");
  Serial.println(responsecode);

}

bool armed = true;
int last_button_state = HIGH;

void loop() {

  //arm or disarm feature
  int button_state = digitalRead(activation_pin);
    if (button_state == LOW && last_button_state == HIGH){
      //means button pressed
      armed = !armed;

      if (!armed){
      http.begin(webhook_URL);
      http.addHeader("Content-Type", "application/JSON");
      std::string message = "Alarm Disarmed";
      std::string json_text = "{\"content\" : \"" + message + "\"}";
      http.POST(json_text.c_str()); // http.POST accepts either C string, Arduino String, or Raw Byte Data
      http.end();
      delay (50);
      }

      if (armed){
      http.begin(webhook_URL);
      http.addHeader("Content-Type", "application/JSON");
      std::string message = "Initializing Alarm...";
      delay(2000);
      std::string json_text = "{\"content\" : \"" + message + "\"}";
      http.POST(json_text.c_str()); // http.POST accepts either C string, Arduino String, or Raw Byte Data
      http.end();
      delay (50);
      }
  }

    if (armed){

          //Setting time
          struct tm timeinfo; // defining the structure
          configTime(0, 0, "pool.ntp.org"); //configTime setting ESP32 time to this

          //now changing the timezone to Dallas Time
          setenv("TZ","CST6CDT,M3.2.0/2,M11.1.0/2", 1);
          tzset();//start using tzset()
          char timestamp[20]; //we will store a formatted time into this to print directly
          getLocalTime(&timeinfo); // set local time into the address of timeinfo
          strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);
          //End: Setting time
          

          int motion = digitalRead(PIR_pin);

          if (motion == HIGH && last_state == false){

            digitalWrite(Buzzer_pin, HIGH);
            Serial.println("Motion Detected");
            http.begin(webhook_URL);
            http.addHeader("Content-Type", "application/JSON");

            //creating message to send
            std::string message = "ALERT!!!   " + std::string(timestamp);
            std::string json_text = "{\"content\" : \"" + message + "\"}";
            int response_code = http.POST(json_text.c_str()); // http.POST accepts either C string, Arduino String, or Raw Byte Data
            Serial.println(response_code);
            Serial.print("ALERT!!!   ");

            http.end();
            delay (50);

          }

          last_state = motion; // this shit stays true when I disarm the system
          //because last_state = false, the loop never enters the discord message part again. 

          if (motion == LOW){
            digitalWrite(Buzzer_pin, LOW);
          }

        delay(30);
      }
    last_button_state = button_state;
    if (!armed){
      digitalWrite(Buzzer_pin, LOW);
      last_state = false;
    
    }

}
