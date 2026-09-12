#include <WiFi.h>
#include <time.h>
#include <FS.h>
#include <SD_MMC.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

const int echopin = 13;
const int trigpin = 12;

struct tm timeinfo;

void setup() {


  Serial.begin(115200);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  //Wi-Fi initialization
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
  }

  //time config
  configTime(0,0,"pool.ntp.org"); // update the timeset of the ESP32 board.

  setenv("TZ", "CST6CDT,M3.2.0/2,M11.1.0/2", 1); // setting new rules for the TZ environment variable.
  tzset(); // "I changed the TZ setting. Start using those timezone rules."

  //SD Card initialization (1-bit mode)
  if (SD_MMC.begin("/sdcard", true)){   //this true means initialize in 1-bit SD mode.
    Serial.println("SD Card ready!");
  }

  else{
    Serial.println("Failed to Initialize SD Card");
  }

  //Create the file to write in
  File file = SD_MMC.open("/data.csv", FILE_APPEND);

  if (file){

    if (file.size() == 0){
      file.println("timestamp, distance (cm)");
    }
  file.close();
  }
}

void loop() {

  //triger the ultrasonic sensor
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin, LOW);

  //Measure how long ECHO stays HIGH
  long duration = pulseIn(echopin, HIGH, 30000);

  //get the time
  getLocalTime(&timeinfo); // the local time of the ESP32 is being saved into timeinfo


  if (duration == 0) {
          // don't do anything. 
      }
  

  else{

    //convert time into distance
    float distance = duration * 0.0343 / 2;

    //show result on Serial Monitor - Optional
    Serial.print("Distance -> ");
    Serial.print(distance);
    Serial.print (" cm   -   ");
    Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");

    char timestamp[20];
    // turns time into nicely formatted text.
    //this function takes a struct pointer. timeinfo is an actual pointer. &timeinfo is the address. 
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo); 

    //Create the file to write in
    File file = SD_MMC.open("/data.csv", FILE_APPEND);

    if (file){

      file.print(timestamp);
      file.print(" , ");
      file.println(distance);

      file.close();
    }




  }
  delay(1000);
}
