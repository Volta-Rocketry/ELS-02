# Pull Request

## Reference Issue
Closes: #3  
Related: #3

---

# Objective
In this part, the data and their physical units are defined, establishing data structures that enable consistent information exchange between roles, avoiding differences in variables or interpretation errors, without depending on the hardware.
## Scope of Changes
The data were standardized by defining variable names, units, and types to ensure compatibility between codebases and avoid errors.
- [ ] Feature
- [ ] Bug fix
- [ ] Refactor
- [ ] Documentation
- [ ] Build / CI
- [ ] Other (specify):
### Affected Components
- Module / Package: Technical Documentation
- Language(s): C++ / Markdown
- Files / Directories modified: docs/technical
## Validation & Testing
N/A

- [ ] Unit tests added or updated
- [ ] Manual testing performed
- [ ] Hardware-in-the-loop (HIL)
- [ ] Simulation / mock data
- [ ] Not tested (justification required):
## Limitations & Future Work
N/A
### Current Limitations
- Limitation: N/A
- Reason: N/A
- Impact: N/A

### Deferred / Future Tasks
- [ ] Follow-up task description (link Issue if applicable)
- [ ] Refactor / optimization
- [ ] Additional testing
- [ ] Documentation improvement

**Notes:**
N/A
# Data Types and Units

* **Acceleration:** Meters per second squared ($m/s^2$) Variable: `accel`
  Type: `float`
* **Linear Velocity:** Meters per second ($m/s$) Variable: `lin_vel`
  Type: `float`
* **Angular Velocity:** Radians per second ($rad/s$). Variable: `ang_vel` Type: `float`
* **Pressure:** Pascals ($Pa$). Variable: `pressure` Type: `float`
* **Temperature:** Kelvin ($K$). Variable: `temp` Type: `float`
* **Time:** Microseconds ($\mu s$) since system startup. Variable: `time_stamp` Type: `uint64_t`

# Data Structures
* **Linear acceleration:**
  * ax: Acceleration on the X axis.
  * ay: Acceleration on the Y axis.
  * az: Acceleration on the Z axis.
  * time_stamp: Time stamp.
```cpp
struct acceleration {
    float ax;
    float ay;
    float az;
    uint64_t time_stamp;
};
```
* **Linear Velocity:**
  * vx: Linear velocity on the X axis.
  * vy: Linear velocity on the Y axis.
  * vz: Linear velocity on the Z axis.
  * time_stamp: Time stamp.
```cpp
struct linear_velocity {
    float vx;
    float vy;
    float vz;
    uint64_t time_stamp;
};
```
* **Angular Velocity:**
  * gx: Angular velocity on the X axis.
  * gy: Angular velocity on the Y axis.
  * gz: Angular velocity on the Z axis.
  * time_stamp: Time stamp.
```cpp
struct angular_velocity {
    float gx;
    float gy;
    float gz;
    uint64_t time_stamp;
};
```
* **Pressure:** 
  * pressure: pressure.
  * time_stamp: Time stamp.
```cpp
struct pressure_data {
    float pressure;
    uint64_t time_stamp;
};
```
* **Temperature:**
  * temp: Temperature.
  * time_stamp: Time stamp.
```cpp
struct temperature_data {
    float temp;
    uint64_t time_stamp;
};
```
# Global Data Container
```cpp
struct global_data {
    uint64_t time_stamp;
    acceleration accel;
    linear_velocity lin_vel;
    angular_velocity ang_vel;
    pressure_data press;
    temperature_data temp;
};

```
