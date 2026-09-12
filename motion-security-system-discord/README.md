# Motion Security System with Discord Alerts

ESP32 security-system practice project using a PIR motion sensor, buzzer, arm/disarm button, and Discord webhook notifications.

## Hardware
- ESP32
- PIR motion sensor
- Buzzer
- Push button

## Features
- Arm/disarm toggle
- PIR motion detection
- Local buzzer alarm
- Timestamped Discord alerts over Wi-Fi
- State-change detection to avoid repeated alerts for the same motion event

## Pins Used
- PIR sensor -> GPIO 23
- Buzzer -> GPIO 4
- Arm/disarm button -> GPIO 19

## Setup
Replace the Wi-Fi and Discord webhook placeholders before uploading to the ESP32. Never commit real credentials or webhook URLs to a public repository.
