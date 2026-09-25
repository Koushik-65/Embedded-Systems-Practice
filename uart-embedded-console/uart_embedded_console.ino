#include <string.h>

char command[50];
int command_index = 0;
bool overflow_buffer = false;
const int led_pin = 5;

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();

    if (c == '\r') return;

    if (c == '\n') {
      if (overflow_buffer) {
        Serial.println("ERROR: Command too long");
      } else {
        command[command_index] = '\0';
        Serial.print("PC: ");
        Serial.println(command);

        if (strcasecmp(command, "LED ON") == 0) {
          digitalWrite(led_pin, HIGH);
          Serial.println("ESP32: LED ON");
        } else if (strcasecmp(command, "LED OFF") == 0) {
          digitalWrite(led_pin, LOW);
          Serial.println("ESP32: LED OFF");
        } else if (command_index > 0) {
          Serial.println("ESP32: Unknown command");
        }
      }

      command_index = 0;
      overflow_buffer = false;
    } else if (!overflow_buffer) {
      if (command_index < 49) {
        command[command_index++] = c;
      } else {
        overflow_buffer = true;
      }
    }
  }
}
