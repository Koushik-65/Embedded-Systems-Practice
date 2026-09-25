<div align="center">

# 💻 ESP32 UART Embedded Console

**A lightweight serial command interface built with manual buffering and command parsing.**

`ESP32` · `C/C++` · `UART` · `Buffers` · `Command Parsing` · `GPIO`

</div>

---

## Overview

This project implements a small embedded command console over UART. Instead of relying on high-level line-reading helpers, incoming serial data is processed one character at a time and stored in a fixed-size command buffer.

The firmware validates input, handles oversized commands, performs case-insensitive parsing, and executes supported commands to control the ESP32.

## Key Features

- 115200-baud UART interface
- Character-by-character input processing
- Fixed-size command buffer
- Buffer-overflow handling
- Case-insensitive command matching
- Simple GPIO control through text commands

## Supported Commands

| Command | Action |
|---|---|
| `LED ON` | Turns the LED on |
| `LED OFF` | Turns the LED off |

## Embedded Concepts

| Concept | Application |
|---|---|
| **UART** | Communication between the ESP32 and serial terminal |
| **Character Buffers** | Stores incoming commands without dynamic allocation |
| **C Strings** | Null-terminated command representation |
| **Input Validation** | Rejects commands that exceed the buffer capacity |
| **Command Parsing** | Maps text input to firmware actions |

## Usage

Open a serial terminal at **115200 baud** with a newline line ending and enter one of the supported commands.

## Platform

ESP32 using the Arduino framework and C/C++.
