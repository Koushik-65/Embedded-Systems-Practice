# Motion Security System with Discord Alerts

ESP32 security-system project that detects motion, provides a local alarm, and sends timestamped alerts to Discord over Wi-Fi.

## Key Features
- PIR motion detection
- Arm/disarm control
- Local buzzer alarm
- Timestamped Discord webhook notifications
- State-change detection to prevent repeated alerts for one motion event

## Concepts Demonstrated
GPIO, sensor interfacing, state-change detection, Wi-Fi networking, HTTP requests, webhooks, and NTP-based timestamps.

## Setup
Wi-Fi credentials and the Discord webhook URL are intentionally excluded from the public source and must be configured before use.
