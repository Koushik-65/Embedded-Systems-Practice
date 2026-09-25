# Ultrasonic Distance Data Logger

ESP32 data-logging project that measures distance with an ultrasonic sensor, timestamps each valid reading, and stores the measurements as CSV data on a microSD card.

## Key Features
- Ultrasonic distance measurement
- NTP-based timestamp synchronization over Wi-Fi
- CSV data logging to microSD
- Serial output for live measurements
- Invalid/timeout readings ignored

## Concepts Demonstrated
GPIO, pulse timing, Wi-Fi, NTP, SD card storage, file I/O, and sensor data logging.

## Setup
Wi-Fi credentials are intentionally excluded from the public source and must be configured before use.
