# ESP32 Reaction Time Tester

Measures how quickly a user presses a button after a buzzer signal. The project uses an interrupt to capture the button press and an ESP32 hardware timer to schedule the next round after a randomized delay.

## Hardware
- ESP32
- Push button
- Buzzer

## Pinout
| Component | ESP32 GPIO |
|---|---:|
| Buzzer | 18 |
| Button | 5 |

## Concepts Demonstrated
- GPIO interrupts
- `micros()` timing
- ESP32 hardware timers
- ISR-safe shared state with `volatile`
- State-based program flow

## Operation
1. The buzzer signals the start of a round.
2. The user presses the button as quickly as possible.
3. The ESP32 calculates and prints the reaction time in milliseconds.
4. A hardware timer waits a random 5-8 seconds before beginning another round.

## Environment
Developed for the ESP32 using the Arduino framework.