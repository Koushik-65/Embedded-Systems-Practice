<div align="center">

# 📊 Ultrasonic Distance Data Logger

**Timestamped ESP32 sensor logging with ultrasonic ranging, NTP synchronization, and microSD storage.**

`ESP32` · `C/C++` · `Wi-Fi` · `NTP` · `microSD` · `File I/O` · `Sensors`

</div>

---

## Overview

This project turns the ESP32 into a standalone sensor data logger. It measures distance using ultrasonic pulse timing, obtains synchronized timestamps over Wi-Fi, and records valid measurements to a CSV file on a microSD card.

The result is persistent, timestamped sensor data that can later be opened or analyzed outside the microcontroller.

## Key Features

- Ultrasonic distance measurement
- Timeout handling for invalid sensor readings
- NTP-based clock synchronization
- Local timezone handling
- Persistent CSV logging to microSD
- Live Serial Monitor output

## Data Flow

```text
Ultrasonic Sensor
       ↓
   ESP32 Timing
       ↓
Distance Calculation
       ↓
 NTP Timestamp
       ↓
   CSV / microSD
```

## Embedded Concepts

| Concept | Application |
|---|---|
| **Pulse Timing** | Converts echo duration into distance |
| **Wi-Fi + NTP** | Provides synchronized timestamps |
| **File I/O** | Appends measurements to persistent storage |
| **microSD** | Stores logged data independently of the ESP32 |
| **Validation** | Ignores sensor timeout readings |

## Output

Measurements are stored in `data.csv` as timestamped distance values.

## Configuration

Wi-Fi credentials are intentionally excluded from the public source and must be configured locally before use.
