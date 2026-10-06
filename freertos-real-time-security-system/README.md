# FreeRTOS Real-Time Security System

ESP32 security system that combines multiple sensors, FreeRTOS tasks, local alarm output, an LCD, and a Blynk dashboard.

I built this project to practice organizing a larger embedded application where several pieces of hardware need to run at different rates without putting everything inside one large `loop()`.

## What it does

The ESP32 monitors three sources of activity:

- **PIR sensor** for motion
- **Ultrasonic sensor** for objects within 20 cm
- **MPU6050** for sudden movement of the device

The system can be armed or disarmed from Blynk. When it is armed and an intrusion is detected, the LED turns on, the LCD displays an alert, and the current alarm state is sent to the dashboard.

## FreeRTOS design

The firmware is divided into separate tasks:

| Task | Purpose |
|---|---|
| `pirTask` | Reads the PIR sensor |
| `ultrasonicTask` | Measures distance |
| `MPUTask` | Reads acceleration, gyro, and temperature data |
| `AlertTask` | Combines sensor data and decides whether an intrusion occurred |
| `lcdTask` | Updates the LCD when alarm state changes |
| `NetworkTask` | Services Blynk and sends dashboard updates |

FreeRTOS queues pass data between the tasks. The sensor queues have a length of one because the security logic needs the **latest state**, not a history of old measurements.

## Hardware

- ESP32
- PIR motion sensor
- HC-SR04 ultrasonic sensor
- MPU6050 accelerometer/gyroscope
- 16x2 I2C LCD
- LED
- Breadboard and jumper wires

### Pin connections

| Device | ESP32 |
|---|---|
| Ultrasonic TRIG | GPIO 13 |
| Ultrasonic ECHO | GPIO 15 |
| PIR OUT | GPIO 5 |
| LED | GPIO 4 |
| I2C SDA | GPIO 32 |
| I2C SCL | GPIO 33 |

> The HC-SR04 ECHO output is 5 V. Use a voltage divider before connecting it to the ESP32's 3.3 V GPIO.

## Dashboard

Blynk virtual pins are used for the remote interface:

| Virtual Pin | Function |
|---|---|
| V0 | Arm / disarm |
| V1 | Buzzer state |
| V2 | LED state |
| V3 | Intrusion state |

Dashboard messages are only sent when the intrusion state changes instead of continuously sending the same state.

## Reliability details

A few failure cases are handled directly in the firmware:

- The ultrasonic read uses a timeout so a missing echo cannot leave the task waiting indefinitely.
- The MPU task is only created if the sensor initializes successfully.
- LCD updates happen only when the intrusion state changes.
- Sensor and network communication are separated using FreeRTOS queues.

## Setup

1. Install the ESP32 Arduino core.
2. Install the **Adafruit MPU6050**, **LiquidCrystal I2C**, and **Blynk** libraries.
3. Copy `secrets.example.h` to `secrets.h`.
4. Add your Wi-Fi and Blynk credentials to `secrets.h`.
5. Configure the Blynk V0-V3 datastreams shown above.
6. Compile and upload `freertos_security_system.ino`.

`secrets.h` is intentionally excluded by the repository's `.gitignore`.

## Current hardware note

The firmware uses the Adafruit MPU6050 interface. If the MPU fails initialization, the rest of the security system continues running without starting the MPU task.

## Concepts practiced

`FreeRTOS` · `Tasks` · `Queues` · `I2C` · `GPIO` · `Sensor Interfacing` · `Wi-Fi` · `Blynk` · `Non-blocking System Design`
