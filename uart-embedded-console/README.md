# ESP32 UART Embedded Console

A small serial command interface for controlling an ESP32. Commands are parsed manually one character at a time.

## Features
- 115200 baud serial interface
- Manual command buffer
- Case-insensitive command parsing
- Command length validation
- LED control commands

## Commands
| Command | Action |
|---|---|
| `LED ON` | Turns GPIO 5 on |
| `LED OFF` | Turns GPIO 5 off |

## Concepts Demonstrated
UART/serial communication, C-style strings, character buffers, command parsing, input validation, and GPIO control.

## Usage
Upload the sketch, open a serial terminal at 115200 baud, select a newline line ending, and enter a supported command.