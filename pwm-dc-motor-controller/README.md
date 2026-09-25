# ESP32 PWM DC Motor Controller

Controls a DC motor through an L293D H-bridge using ESP32 PWM. Motor speed ramps automatically while a push button reverses direction.

## Hardware
- ESP32
- L293D H-bridge
- DC motor
- Push button
- External motor power supply

## Pinout
| Signal | ESP32 GPIO |
|---|---:|
| L293D Enable / PWM | 4 |
| L293D Input 1 | 25 |
| L293D Input 2 | 27 |
| Direction button | 5 |

## Features
- 1 kHz, 8-bit PWM motor-speed control
- Automatic duty-cycle ramp
- H-bridge direction control
- Button interrupt for direction changes
- Hardware timer for periodic speed updates

## Concepts Demonstrated
PWM, GPIO, interrupts, hardware timers, H-bridge motor control, and state management.

> The ESP32 must not drive the motor directly. Use the motor driver and an appropriate motor power source, with a common ground.