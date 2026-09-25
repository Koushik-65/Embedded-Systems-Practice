<div align="center">

# 🚨 ESP32 Motion Security System

**Network-connected motion detection with local alarms, state-aware event handling, and timestamped Discord notifications.**

`ESP32` · `C/C++` · `PIR` · `Wi-Fi` · `HTTP` · `Webhooks` · `NTP`

</div>

---

## Overview

This project implements a small connected security system around the ESP32. When armed, a PIR sensor detects motion, activates a local buzzer, and sends a timestamped alert through a Discord webhook.

State-change detection prevents the firmware from repeatedly sending notifications while the same motion event remains active. The system can also be armed or disarmed locally.

## Key Features

- Arm/disarm system state
- PIR-based motion detection
- Local audible alarm
- Timestamped remote notifications
- Wi-Fi and HTTP communication
- State-change detection to suppress duplicate alerts

## Event Flow

```text
Motion Detected
      ↓
State Change Check
      ↓
 ┌───────────────┐
 │ Local Buzzer  │
 └───────────────┘
      ↓
NTP Timestamp
      ↓
HTTP Webhook
      ↓
Discord Alert
```

## Embedded Concepts

| Concept | Application |
|---|---|
| **PIR Sensing** | Detects environmental motion |
| **State Detection** | Sends one alert per motion event |
| **Wi-Fi** | Provides network connectivity |
| **HTTP/Webhooks** | Sends remote event notifications |
| **NTP** | Adds synchronized timestamps to alerts |
| **System State** | Controls armed and disarmed behavior |

## Configuration

Wi-Fi credentials and the Discord webhook URL are intentionally excluded from the public source and must be configured locally before use.
