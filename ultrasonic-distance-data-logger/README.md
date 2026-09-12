# Ultrasonic Distance Data Logger

Measures distance using an ultrasonic sensor and records timestamped readings to a microSD card.

## Hardware
- ESP32
- Ultrasonic distance sensor
- microSD card

## Features
- Ultrasonic distance measurement
- NTP-based time synchronization
- Central Time timezone configuration
- CSV logging to microSD
- Serial Monitor output

## Wiring Used
- TRIG -> GPIO 12
- ECHO -> GPIO 13

## Output
The program creates `data.csv` with timestamp and distance values.

## Setup
Before uploading, replace the Wi-Fi placeholders in the sketch with your own credentials. Do not commit real credentials to a public repository.
