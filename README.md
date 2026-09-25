<div align="center">

# Embedded Systems Practice

**A growing collection of ESP32 firmware projects built to explore real embedded-systems concepts through hands-on development.**

`ESP32` · `C/C++` · `GPIO` · `UART` · `I2C` · `ADC` · `PWM` · `Interrupts` · `Timers` · `Wi-Fi`

</div>

---

## Overview

This repository documents my progression in embedded systems and firmware development. Each project focuses on a different part of microcontroller programming—from low-level GPIO and timing to communication protocols, motor control, networking, and data logging.

Rather than isolated code exercises, the projects combine hardware and firmware into small working systems and progressively introduce more advanced embedded concepts.

## Projects

### ⏱️ [Reaction Time Tester](./reaction-time-tester)
Interrupt-driven reaction timer that measures button response time with microsecond-resolution timing and schedules new rounds using an ESP32 hardware timer.

**Focus:** `Interrupts` `micros()` `Hardware Timers` `Volatile State`

### ⚙️ [PWM DC Motor Controller](./pwm-dc-motor-controller)
Controls DC motor speed and direction through an L293D H-bridge, using PWM for speed control and interrupt-driven input for direction changes.

**Focus:** `PWM` `H-Bridge` `Interrupts` `Hardware Timers`

### 💻 [UART Embedded Console](./uart-embedded-console)
A lightweight serial command interface built around manual character buffering, command parsing, validation, and GPIO control.

**Focus:** `UART` `Buffers` `C Strings` `Command Parsing`

### 📐 [MPU6050 + LCD Sensor Monitor](./mpu6050-lcd-sensor-monitor)
Reads motion, temperature, and analog data and presents live measurements on an LCD while sharing an I2C bus between multiple devices.

**Focus:** `I2C` `ADC` `Sensor Interfacing` `Display Output`

### 📊 [Ultrasonic Distance Data Logger](./ultrasonic-distance-data-logger)
Collects ultrasonic distance measurements, synchronizes timestamps over NTP, and stores readings as CSV data on microSD.

**Focus:** `Sensor Timing` `Wi-Fi` `NTP` `microSD` `File I/O`

### 🚨 [Motion Security System](./motion-security-system-discord)
Motion-triggered security system with arm/disarm control, local alarm output, state-change detection, and timestamped remote alerts over Wi-Fi.

**Focus:** `PIR Sensing` `State Detection` `HTTP` `Webhooks` `Wi-Fi`

---

## Technical Areas

| Area | Experience in this repository |
|---|---|
| **Microcontroller** | ESP32 |
| **Languages / Framework** | C/C++, Arduino framework |
| **Communication** | UART, I2C, HTTP |
| **Hardware Control** | GPIO, PWM, ADC, interrupts, hardware timers |
| **Sensors & Devices** | MPU6050, ultrasonic sensor, PIR sensor, LCD, DC motor |
| **Connectivity & Storage** | Wi-Fi, NTP, webhooks, microSD, CSV logging |

## Repository Layout

```text
Embedded-Systems-Practice/
├── reaction-time-tester/
├── pwm-dc-motor-controller/
├── uart-embedded-console/
├── mpu6050-lcd-sensor-monitor/
├── ultrasonic-distance-data-logger/
└── motion-security-system-discord/
```

Each directory contains the firmware source and a focused README describing the project's purpose, features, and embedded concepts.

## Security

Network credentials, webhook URLs, and other secrets are intentionally excluded from the public source. Projects that require them use placeholders that must be configured locally before flashing.

---

<div align="center">

**Built while learning embedded systems through implementation, debugging, and experimentation.**

</div>
