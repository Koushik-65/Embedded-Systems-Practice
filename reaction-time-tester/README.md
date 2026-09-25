# ESP32 Reaction Time Tester

Measures how quickly a user presses a button after a buzzer signal. An interrupt captures the button press, while an ESP32 hardware timer schedules each new round after a randomized delay.

## Key Features
- Reaction-time measurement using `micros()`
- Interrupt-driven button input
- Randomized 5–8 second delay between rounds
- Hardware timer for round scheduling

## Concepts Demonstrated
GPIO interrupts, precise timing, ESP32 hardware timers, ISR-safe shared state with `volatile`, and state-based program flow.

## Environment
ESP32 using the Arduino framework.
