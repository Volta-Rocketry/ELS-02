#ifndef TELEMETRY_STRUCTURES_H
#define TELEMETRY_STRUCTURES_H

#include <stdint.h>
// Motion and Orientation
struct acceleration {
    float ax, ay, az;
    uint64_t timestamp;
};

struct linear_velocity {
    float vx, vy, vz;
    uint64_t timestamp;
};

struct angular_velocity {
    float gx, gy, gz;
    uint64_t timestamp;
};

struct magnetometer {
    float mx, my, mz;
    uint64_t timestamp;
};

// Structural Measurements
struct bulkhead_deformation {
    float bulk_def_1, bulk_def_2, bulk_def_3;
    uint64_t timestamp;
};

struct airframe_deformation {
    float air_def_1, air_def_2, air_def_3, air_def_4;
    uint64_t timestamp;
};

struct airframe_stress {
    float air_load_1, air_load_2, air_load_3, air_load_4;
    uint64_t timestamp;
};

// Environment and Avionics
struct barometer_data {
    float pressure;
    float alt;
    uint64_t timestamp;
};

struct temperature_data {
    float temp_1, temp_2, temp_3, temp_4;
    uint64_t timestamp;
};

struct audio_data {
    int16_t audio;
    uint64_t timestamp;
};

// Processed Data 
struct estimated_data {
    float px, py, pz;
    float sx, sy, sz;
    uint64_t timestamp;
};

struct filtered_data {
    float accel_f[3];
    float gyro_f[3];
    float alt_f;
    uint64_t timestamp;
};

// Global Data Container 
struct global_data {
    uint64_t timestamp; 
    
    acceleration accel;
    linear_velocity lin_vel;
    angular_velocity ang_vel;
    magnetometer mag;
    barometer_data baro;
    
    bulkhead_deformation bulk_def;
    airframe_deformation air_def;
    airframe_stress air_load;
    
    temperature_data temp;
    audio_data audio;

    filtered_data filtered;
    estimated_data estimated;
};
#endif