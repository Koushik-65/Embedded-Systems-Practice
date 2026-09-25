# MPU6050 + LCD Sensor Monitor

ESP32 sensor-monitoring project that combines an MPU6050 inertial measurement unit, a 16x2 I2C LCD, and an analog potentiometer.

## Hardware
- ESP32
- MPU6050 accelerometer/gyroscope
- 16x2 I2C LCD (`0x27`)
- Potentiometer

## Pinout
| Signal | ESP32 GPIO |
|---|---:|
| I2C SDA | 26 |
| I2C SCL | 25 |
| Potentiometer output | 34 |

The MPU6050 uses I2C address `0x68`.

## Measurements
The display cycles through potentiometer ADC value, MPU6050 temperature, three-axis acceleration, and three-axis gyroscope data.

## Concepts Demonstrated
I2C communication, multiple devices on one bus, ADC input, sensor libraries, structured sensor data, and LCD output.

## Required Libraries
- Adafruit MPU6050
- Adafruit Unified Sensor
- LiquidCrystal I2C

The firmware checks MPU6050 initialization and stops with an error message if the sensor cannot be found.