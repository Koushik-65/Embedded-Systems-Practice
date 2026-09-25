<div align="center">

# ⚙️ ESP32 PWM DC Motor Controller

**PWM-based DC motor speed and direction control using an ESP32 and L293D H-bridge.**

`ESP32` · `C/C++` · `PWM` · `Interrupts` · `Hardware Timers` · `H-Bridge`

</div>

---

## Overview

This project explores embedded motor control by driving a DC motor through an L293D H-bridge. The ESP32 generates PWM for speed control, automatically ramps the duty cycle, and responds to interrupt-driven input to reverse direction.

## Key Features

- PWM-based motor speed control
- Automatic duty-cycle ramping
- Bidirectional H-bridge control
- Interrupt-driven direction changes
- Hardware timer for periodic speed updates

## Control Flow

The firmware separates motor speed from direction: PWM controls the effective motor power while the H-bridge inputs determine rotation direction. A hardware timer advances the speed ramp, and button input can request a direction change without continuously polling for it.

## Embedded Concepts

| Concept | Application |
|---|---|
| **PWM** | Controls motor speed through duty cycle |
| **H-Bridge** | Enables forward and reverse motor operation |
| **GPIO Interrupts** | Responds to direction-change input |
| **Hardware Timer** | Provides periodic speed-ramp timing |
| **State Management** | Tracks duty cycle and current direction |

## Platform

ESP32 using the Arduino framework and C/C++.
