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

### Multi-Rate Synchronization & Data Freshness

Since sensors operate at different sampling frequencies, the system employs a Global Bitmask Strategy to minimize memory overhead while maintaining temporal precision.

* **Global Structure:** The system records a fixed-size `StructGlobalData` packet at the target loop rate (100Hz). This packet contains a single `uint32_t` Global Timestamp.

* **Freshness Bitmask:** A 16-bit header flag is used and each bit corresponds to a specific sensor group.

* **Synchronization Logic:** 

    * **Fast Sensors:** Update every cycle. Their corresponding freshness bit is set to 1 (TRUE) in every packet.

    * **Slow Sensors:** Update only when new data is available.
        * **New Data:** The value is updated in the structure, and the freshness bit is set to 1 (TRUE).
        * **No New Data:** The system retains the previous value, and the freshness bit is set to 0 (FALSE).

*Analysis Note:* During post-flight analysis, the parser reads the Bitmask first. If a sensor's bit is 0, the software identifies the data as a "repeat" and can either discard it or use it for interpolation, ensuring that only physically measured events are processed without timing ambiguity.

---
