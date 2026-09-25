<div align="center">

# 📐 MPU6050 + LCD Sensor Monitor

**Multi-sensor ESP32 monitor combining inertial measurements, analog input, and live LCD output.**

`ESP32` · `C/C++` · `I2C` · `ADC` · `MPU6050` · `LCD`

</div>

---

## Overview

This project combines multiple input and output devices into one embedded monitoring system. The ESP32 reads acceleration, angular velocity, and temperature from an MPU6050 while also sampling an analog potentiometer. Measurements are presented live on a 16×2 LCD.

The project demonstrates how multiple I2C peripherals and analog inputs can be coordinated within a single firmware application.

## Measurements

- Three-axis acceleration
- Three-axis gyroscope data
- MPU6050 temperature
- Analog potentiometer value

## Key Features

- Live sensor acquisition
- Multiple devices sharing an I2C bus
- Analog-to-digital conversion
- LCD-based embedded user output
- Sensor initialization checking

## Embedded Concepts

| Concept | Application |
|---|---|
| **I2C** | Communicates with the MPU6050 and LCD |
| **ADC** | Samples the analog potentiometer |
| **Sensor Interfacing** | Acquires structured motion and temperature data |
| **Display Output** | Presents live measurements locally |
| **Initialization Checks** | Detects sensor startup failures |

## Software

Uses the Adafruit MPU6050, Adafruit Unified Sensor, and LiquidCrystal I2C libraries with the Arduino framework.
