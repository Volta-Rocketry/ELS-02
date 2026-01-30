# Objective
In this part, the data and their physical units are defined, establishing data structures that enable consistent information exchange between roles, avoiding differences in variables or interpretation errors, without depending on the hardware.
# Data Standards and Physical Units
* **Acceleration:** Meters per second squared ($m/s^2$). Variable: `accel`
  Type: `float`
* **Linear Velocity:** Meters per second ($m/s$). Variable: `linVel`
  Type: `float`
* **Angular Velocity:** Radians per second ($rad/s$). Variable: `angVel` Type: `float`
* **Magnetometer:** microteslas ($\mu T$). Variable: `mag` Type: `float`
* **Pressure:** Pascals ($Pa$). Variable: `pressure` Type: `float`
* **Altitude:** Meters ($m$). Variable: `alt` Type: `float`
* **Temperature:** Kelvin ($K$). Variable: `temp` Type: `float`
* **Deformation:** Strain ($ε$) (dimensionless ($mm/mm$)). Variable: `def` Type: `float`
* **Loads:** Newtons ($N$). Variable: `load` Type: `float`
* **Audio:** Amplitude. Variable: `audio` Type: `int16_t`
* **Time:** Milliseconds ($ms$) since system startup. Variable: `timestamp` Type: `uint32_t`
# Data Structures
* **Motion and Orientation**


**Linear acceleration:**

```cpp
struct StructAcceleration {
    float ax; // Acceleration on the X axis
    float ay; // Acceleration on the Y axis
    float az; // Acceleration on the Z axis
    uint32_t timestamp; // Timestamp
};
```
**Linear Velocity:**
```cpp
struct StructLinearVelocity {
    float vx; // linear velocity on the X axis
    float vy; // Linear velocity on the Y axis
    float vz; // Linear velocity on the Z axis
    uint32_t timestamp; // Timestamp
};
```
**Angular Velocity:**
```cpp
struct StructAngularVelocity {
    float gx; // Angular velocity on the X axis
    float gy; // Angular velocity on the Y axis
    float gz; // Angular velocity on the Z axis
    uint32_t timestamp; // Timestamp
};
```
**Magnetometer:**
```cpp
struct StructMagnetometer {
    float mx; // Magnetic field on the X axis
    float my; // Magnetic field on the Y axis
    float mz; // Magnetic field on the Z axis
    uint32_t timestamp; // Timestamp
};
```
* **Structural Measurements**


**Bulkhead Deformation:**
```cpp
struct StructBulkheadDeformation {
    float bulkDef1; // Bulkhead deformation (sensor "1")
    float bulkDef2; // Bulkhead deformation (sensor "2")
    float bulkDef3; // Bulkhead deformation (sensor "3")
    uint32_t timestamp; // Timestamp
};
```
**Airframe Deformation:**
```cpp
struct StructAirframeDeformation {
    float airDef1; // Airframe deformation (sensor "1")
    float airDef2; // Airframe deformation (sensor "2")
    float airDef3; // Airframe deformation (sensor "3")
    float airDef4; // Airframe deformation (sensor "4")
    uint32_t timestamp; // Timestamp
};
```
**Airframe Loads:**
```cpp
struct StructAirframeLoad {
    float airLoad1; // Airframe load (sensor "1")
    float airLoad2; // Airframe load (sensor "2")
    float airLoad3; // Airframe load (sensor "3")
    float airLoad4; // Airframe load (sensor "4")
    uint32_t timestamp; // Timestamp
};
```
* **Environment and Avionics**


**Altitude and Pressure:** 
```cpp
struct StructBarometer {
    float pressure;    // Pressure
    float alt;         // Altitude
    uint32_t timestamp; // Timestamp
};
```
**Temperature:**
```cpp
struct StructTemperature {
    float temp1; // Temperature (sensor "1")
    float temp2; // Temperature (sensor "2")
    float temp3; // Temperature (sensor "3")
    float temp4; // Temperature (sensor "4")
    uint32_t timestamp; // Timestamp
};
```
**Audio:**
```cpp
struct StructAudio {
    int16_t audio; // Mic sensor
    uint32_t timestamp; // Timestamp
};
```
# Processed Data
This section defines variables for processed data to ensure that only validated signals are used, reducing noise propagation and minimizing errors.



**State Estimations:**
Stores estimated position and velocity obtained from acceleration measurements.
```cpp
struct StructEstimated {
  // Estimated position (m)
    float px; // X axis
    float py; // Y axis
    float pz; // Z axis
  // Estimated velocity (m/s)
    float sx; // X axis
    float sy; // Y axis
    float sz; // Z axis
    uint32_t timestamp; // Timestamp
};
```
**Digital Filtering:**
Stores values smoothed using filtering algorithms.
```cpp
struct filtered_data {
    float accelF[3]; // [ax, ay, az] filtered acceleration
    float angVelF[3];  // [gx, gy, gz] filtered velocity
    float altF;      // Filtered altitude
    uint32_t timestamp; // Timestamp
};
```
# Global Data Container
```cpp
struct StructGlobalData {
    uint32_t timestamp; 
    
    // Motion
    StructAcceleration accel;
    StructLinearVelocity linVel;
    StructAngularVelocity angVel;
    StructMagnetometer mag;
    StructBarometer baro;

    // Structural
    StructBulkheadDeformation bulkDef;
    StructAirframeDeformation airDef;
    StructAirframeLoad airLoad;

    // Environment
    StructTemperature temp;
    StructAudio audio;

    // Processed Data
    StructFiltered filtered;
    StructEstimated estimated;
};
```
