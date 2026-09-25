# Embedded Systems Practice

Hands-on ESP32 projects exploring firmware fundamentals: GPIO, interrupts, hardware timers, PWM, UART, I2C, ADC, networking, sensors, and data logging.

## Project Showcase

| Project | What it demonstrates |
|---|---|
| [Ultrasonic Distance Data Logger](./ultrasonic-distance-data-logger) | Ultrasonic ranging, NTP timestamps, microSD/CSV logging |
| [Motion Security System](./motion-security-system-discord) | PIR sensing, Wi-Fi/HTTP, state-change detection, remote alerts |
| [Reaction Time Tester](./reaction-time-tester) | GPIO interrupts, `micros()`, hardware timers, ISR state |
| [PWM DC Motor Controller](./pwm-dc-motor-controller) | PWM, L293D H-bridge, motor direction, interrupts |
| [UART Embedded Console](./uart-embedded-console) | Serial communication, manual command parsing, buffer handling |
| [MPU6050 + LCD Sensor Monitor](./mpu6050-lcd-sensor-monitor) | I2C, MPU6050 IMU, LCD output, ADC |

## Platform

- **Microcontroller:** ESP32
- **Framework:** Arduino / C++
- **Interfaces:** GPIO, UART, I2C, ADC, PWM
- **Other topics:** interrupts, hardware timers, Wi-Fi, HTTP, NTP, microSD storage

## Repository Structure

Each project has its own directory containing the firmware and a README with hardware, pin assignments, behavior, and concepts demonstrated.

## Security

Wi-Fi credentials, webhook URLs, and other secrets are intentionally excluded from the public source. Replace placeholders locally before flashing projects that require network access.

## About

This repository documents my progression in embedded-systems and firmware development through practical ESP32 projects.