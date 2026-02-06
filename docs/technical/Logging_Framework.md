# Define and Implement Logging Framework

## Purpose

Define the telemetry storage strategy, ensuring data integrity under high-dynamic flight conditions through serialization protocols and fail-safe hardware utilization.

---

## Storage Architecture

The system implements a deferred storage architecture. Flight telemetry is recorded exclusively to the integrated Flash module during flight, with a manual download to an SD card inserted after the flight by activating a switch/button.

### Justification

* **Mechanical immunity:** The soldered-down Flash module is immune to the high-frequency vibrations and G-forces that typically cause momentary contact failures in mechanical SD card slots.
    
* **Deterministic timing:** Flash module provides predictable write latencies, eliminating the blocking delays inherent to SD card modules.

* **Data recovery:** Implementing post-flight storage on an SD card prevents damage to the card itself or other components. It also facilitates portability and data retrieval after a flight.

### Architecture Diagram 

```mermaid
graph LR
    A[Power ON] --> B{Switch/button State?}
    
    B -- "OFF (Flight Mode)" --> C(Wait for Launch Detect)
    C --> D[Recording to FLASH]
    D --> E(Landing / Memory Full)
    E --> F[Stop Recording]
    
    B -- "ON (Transfer Mode)" --> H{SD Card Present?}
    H -- No --> I(Blink Error LED)
    H -- Yes --> J[DUMP Flash to SD]
    J --> K(Blink Success LED)
    K --> L[Erase Flash]
```

---

## Data Serialization & Format

To ensure high-performance logging without compromising CPU cycles, the system avoids text conversion (CSV) during flight. Instead, it implements a airect binary serialization protocol.

### Storage Format

Data is stored in .bin files by directly dumping the memory block of the `StructGlobalData` structure into the storage media.

### Data Structure

The log follows a Nested Structure Architecture defined by the `StructGlobalData` container. This ensures strict separation between raw sensor inputs and algorithmic outputs within the same synchronized frame.

(Note: Full structure definition provided in [constants.h](.../.../ELS-02/include/constants.h))

### Multi-Rate Synchronization

Since sensors operate at different frequencies, the system uses a "snapshot" strategy enabled by the individual timestamps inside each sub-structure.

* **Global Timestamp:** The system records a full `StructGlobalData` snapshot at the target loop rate.

* **Data Freshness Logic:** 

    * **Fast Sensors:** Update every cycle. Their local timestamp matches the Global Timestamp.

    * **Slow Sensors:** Update only when new data is ready. If data is not ready, the previous value and previous timestamp are retained.

*Analysis Note:* During post-flight analysis, duplicate timestamps in specific sub-structures effectively flag "held" data, allowing the analysis software to reconstruct the exact timeline without interpolation errors.

---
