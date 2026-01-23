#pragma once

#include <stdint.h>

#define LED_PIN 13
// Baud Rate
extern const uint32_t BAUD_RATE;

// PIN DEFINITIONS
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SCK_PIN 12

#define SD_CS_PIN 4
#define FLASH_CS_PIN 5
#define ALT_CS_PIN 6
#define IMU_CS_PIN 7

#define SDA_PIN 8
#define SCL_PIN 9

#define MIC_PIN 14

// Bulkhead Deformation Sensor Pins
#define BULK1_DT_PIN 15
#define BULK1_SCK_PIN 18

#define BULK2_DT_PIN 16
#define BULK2_SCK_PIN 19

#define BULK3_DT_PIN 17
#define BULK3_SCK_PIN 20

// Airframe Deformation Sensor Pins
#define AIR_DEF1_DT_PIN 35
#define AIR_DEF1_SCK_PIN 21

#define AIR_DEF2_DT_PIN 36
#define AIR_DEF2_SCK_PIN 47

#define AIR_DEF3_DT_PIN 37
#define AIR_DEF3_SCK_PIN 48

#define AIR_DEF4_DT_PIN 1
#define AIR_DEF4_SCK_PIN 2

// Airframe Load Sensor Pins

// Temperature Sensor Pins

// Timing
extern const int BLINK_MS;
extern const int SAMPLING_MS;

// Telemetry Structures
// Motion and Orientation
struct StructAcceleration {
    float ax, ay, az;
    uint32_t timestamp;
};

struct StructLinearVelocity {
    float vx, vy, vz;
    uint32_t timestamp;
};

struct StructAngularVelocity {
    float gx, gy, gz;
    uint32_t timestamp;
};

struct StructMagnetometer {
    float mx, my, mz;
    uint32_t timestamp;
};

// Structural Measurements
struct StructBulkheadDeformation {
    float bulkDef1, bulkDef2, bulkDef3;
    uint32_t timestamp;
};

struct StructAirframeDeformation {
    float airDef1, airDef2, airDef3, airDef4;
    uint32_t timestamp;
};

struct StructAirframeLoad {
    float airLoad1, airLoad2, airLoad3, airLoad4;
    uint32_t timestamp;
};

// Environment and Avionics
struct StructBarometer {
    float pressure, alt;
    uint32_t timestamp;
};

struct StructTemperature {
    float temp1, temp2, temp3, temp4;
    uint32_t timestamp;
};

struct StructAudio {
    int16_t audio;
    uint32_t timestamp;
};

// Processed Data 
struct StructEstimated {
    float px, py, pz;
    float sx, sy, sz;
    uint32_t timestamp;
};

struct StructFiltered {
    float accelF[3];
    float angVelF[3];
    float altF;
    uint32_t timestamp;
};

// Global Data Container 
struct StructGlobalData {
    uint32_t timestamp; 
    
    StructAcceleration accel;
    StructLinearVelocity linVel;
    StructAngularVelocity angVel;
    StructMagnetometer mag;
    StructBarometer baro;

    StructBulkheadDeformation bulkDef;
    StructAirframeDeformation airDef;
    StructAirframeLoad airLoad;

    StructTemperature temp;
    StructAudio audio;

    StructFiltered filtered;
    StructEstimated estimated;
};