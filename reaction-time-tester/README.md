<div align="center">

# ⏱️ ESP32 Reaction Time Tester

**Interrupt-driven reaction timer with microsecond-resolution measurement and hardware-timed rounds.**

`ESP32` · `C/C++` · `GPIO Interrupts` · `Hardware Timers` · `micros()`

</div>

---

## Overview

This project measures how quickly a user reacts to a buzzer signal. A GPIO interrupt captures the button press immediately, while `micros()` provides precise timing. An ESP32 hardware timer schedules the next round after a randomized delay.

## Key Features

- Microsecond-resolution reaction-time measurement
- Interrupt-driven button capture
- Randomized 5–8 second delay between rounds
- Hardware-timer-based round scheduling
- ISR-safe shared state using `volatile`

## How It Works

1. The system waits for a randomized delay.
2. The buzzer signals the start of the round.
3. The button interrupt records the user's response time.
4. The result is calculated and printed in milliseconds.
5. The hardware timer schedules the next round.

## Embedded Concepts

| Concept | Application |
|---|---|
| **GPIO Interrupts** | Captures the button press without polling |
| **`micros()`** | Measures reaction time with fine resolution |
| **Hardware Timers** | Schedules new rounds independently of normal loop timing |
| **`volatile` State** | Safely shares ISR-updated flags with the main program |

## Platform

ESP32 using the Arduino framework and C/C++.
