# Flight Logging Framework

## Purpose

Define how flight data is stored and serialized during flight.

---

## Overview

This module is responsible for capturing, serializing, and storing critical telemetry data onto an SD card in real-time.

The system is designed for high-performance writing using a RAM Buffer and a synchronized CSV format, ensuring that raw sensor data and Kalman Filter estimates are perfectly aligned in time.

---

## Project Structure

| File | Type | Description |
| :--- | :--- | :--- |
| `telemetry_structures.h` | **Data** | Defines the master global_data structure and all sensor sub-structs. |
| `flight_logger.h` | **Interface** | Header file defining the FlightLogger class and public methods. |
| `flight_logger.cpp` | **Logic** | Implements the RAM buffering logic and SD card flush operations. |
| `interpreter.py` | **Test** | Python script to validate CSV integrity and convert logs to Excel. |
| `flight_log.csv` | **Output** | The resulting file stored on the SD card. |

---

## Architecture

### 1. Data Standardization
To ensure data consistency, all telemetry is aggregated into a single container struct (global_data) before processing.

### 2. Buffering Mechanism
Direct SD writing is slow. To prevent blocking the main flight loop, this module uses a Two-Stage Write Process:

1.  **RAM Stage:** Data is instantly saved to `ramBuffer[BUFFER_SIZE]` (Size: 100 packets).
2.  **SD Flush:** Once the buffer is full, a bulk write operation flushes data to the physical SD card.

---
