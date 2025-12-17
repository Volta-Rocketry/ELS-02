# Working Model and Roles

## 1. Document Objective

This project focuses exclusively on **software development** for an onboard rocket measurement platform.  
All electronics hardware design is handled by a separate team.

The software stack must:
- Acquire real-time sensor data from flight electronics
- Estimate flight states (acceleration, velocity, position, attitude where applicable)
- Detect flight phases (pre-flight, boost, coast, deployment, descent)
- Compute structural metrics (fuselage deformation indicators, recovery bulkhead loads)
- Log and structure data for post-flight analysis
- Run on yet-to-be-finalized embedded hardware using **C++ and PlatformIO**

The output of this project is **production-grade embedded firmware**, suitable for academic flight use and open-source release.

This document establishes:

* Role definitions
* High-level task distribution
* Interaction and authorization rules
* Workflow and change management

---

## 2. Working Principles

Given a two-person team and the nature of the work, the project is split into **two complementary roles**.

* Each technical domain has a **clearly identified owner**.
* Decisions are based on **defined inputs and agreed interfaces**.
* Technical information is frozen at specific milestones (*design freezes*).
* Work progresses through **coordination and review**, not unilateral changes.

## 3. Role Definition

### 3.1 Role A — Embedded Systems & Hardware Abstraction

**Responsibility Domain**
- Low-level interaction with hardware
- Runtime stability and performance
- Data acquisition reliability

**Responsibilities**
- Interpretation and transformation of raw data
- Define and implement hardware abstraction layers (HAL)
- Implement sensor drivers and communication interfaces
- Define timing models (sampling rates, interrupts, buffers)
- Manage PlatformIO configuration and board support packages

**Explicit Boundaries**
- Does not implement estimation algorithms or flight logic
- Does not define physical models or filtering strategies

---

### Role B — Flight Logic & Data Processing

**Responsibility Domain**
- Flight state estimation and logic
- Scientific and structural computation

**Responsibilities**
- Define flight phase detection logic
- Implement estimation pipelines (filters, integrators, observers)
- Define data structures for measurements and states
- Implement deformation and load estimation logic
- Define logging formats and data semantics

**Explicit Boundaries**
- Does not implement hardware drivers or low-level I/O
- Does not manage MCU-specific configuration

---

## 4. Interfaces and Interaction Rules

### 3.1 Software Architecture Boundary

The system is split into **three layers**:

- [ HAL & Drivers ] ← Role A ownership
- [ Data Interface Layer ] ← Joint contract
- [ Estimation & Logic ] ← Role B ownership

### 3.2 Interface Contracts

- Sensor outputs are exposed as **typed data structures**, not raw registers
- Timing assumptions (sample rate, latency, jitter) are explicitly documented
- No cross-layer access is allowed (logic cannot access drivers directly)

All interfaces must be defined in header files and documented before implementation.

---

## 4. Workflow and Milestones

### 4.1 High-Level Task Distribution

The following task distribution defines **ownership domains**, not execution order.  
Tasks are expected to overlap in time and be revisited iteratively as interfaces mature.

---

### Role A — Embedded Systems & Hardware Abstraction

- Firmware requirements consolidation from hardware capabilities
- Definition of embedded software architecture (layering, constraints)
- Definition of HAL boundaries and interface contracts
- PlatformIO environment setup and board configuration
- MCU- and sensor-level integration planning
- Timing, sampling, and resource budgeting
- Build system maintenance and flashing workflows
- Low-level integration reviews and runtime validation

---

### Role B — Flight Logic & Data Processing

- Definition of flight data models and state representations
- Definition of flight phase logic and transitions
- Estimation strategy definition (filters, observers, integration)
- Structural computation model definition (loads, deformation indicators)
- Data semantics and logging requirements
- Algorithm validation using simulated and replayed data
- Post-processing and analysis readiness considerations

---

### 4.2 Milestones Overview

The milestones below describe **integration maturity**, not rigid phases.  
Multiple milestones may be partially active in parallel.


#### Milestone 1 — Architecture Definition
- System decomposition
- Data interfaces frozen
- Flight data model agreed

#### Milestone 2 — Independent Module Development
- HAL and drivers developed in isolation
- Estimation and logic developed using mock data

#### Milestone 3 — Integration
- Real sensor data connected to logic layer
- End-to-end data flow validated

#### Milestone 4 — Flight Readiness
- Timing validation
- Stress testing
- Logging verification

## 5. Quality and Validation Rules

- All modules must compile independently
- All interfaces require header-level documentation
- Simulation or replay data must exist for all estimation logic
- No blocking loops in flight-critical paths
- Deterministic behavior prioritized over feature count

---

## 6. Change Management

Any modification after a defined milestone requires:

* A documented change request
* Assessment of technical impact
* Agreement between both roles

This ensures changes are deliberate and traceable.

---