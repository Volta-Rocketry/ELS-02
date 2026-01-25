#include "flight_logger.h"

FlightLogger::FlightLogger(int csPin) {
    chipSelect = csPin;
    bufferIndex = 0;
}

// Hardware (SD Card)
bool FlightLogger::begin() {
    // Starting SD
    if (!SD.begin(chipSelect)) {
        return false; // The start failed
    }

    File dataFile = SD.open("/flight_log.csv", FILE_WRITE);

    if (dataFile) {
        dataFile.close();
        return true;
    }

    return false; // Document creation failed
}

// Buffer management
void FlightLogger::logGlobalState(global_data newData) {
    // Buffer
    if (bufferIndex < BUFFER_SIZE) {
        ramBuffer[bufferIndex] = newData;
        bufferIndex++;
    }

    // Flush
    if (bufferIndex >= BUFFER_SIZE) {
        flush();
    }
}

// Flush
void FlightLogger::flush() {
    File dataFile = SD.open("/flight_log.csv", FILE_WRITE);

    if (dataFile) {
        for (int i = 0; i < bufferIndex; i++) {
            global_data d = ramBuffer[i];

            dataFile.printf(
                // Spaces
                "%llu,"                   // Timestamp
                "%.2f,%.2f,%.2f,"         // Accel (ax, ay, az)
                "%.2f,%.2f,%.2f,"         // Lin Vel (vx, vy, vz)
                "%.2f,%.2f,%.2f,"         // Ang Vel (gx, gy, gz)
                "%.2f,%.2f,%.2f,"         // Mag (mx, my, mz)
                "%.4f,%.4f,%.4f,"         // Bulk Def
                "%.4f,%.4f,%.4f,%.4f,"    // Air Def
                "%.2f,%.2f,%.2f,%.2f,"    // Air Load
                "%.2f,%.2f,"              // Baro (Pressure, Alt)
                "%.1f,%.1f,%.1f,%.1f,"    // Temps
                "%d,"                     // Audio
                "%.2f,%.2f,%.2f,"         // Filt Accel (Array [0],[1],[2])
                "%.2f,%.2f,%.2f,"         // Filt Gyro (Array [0],[1],[2]) 
                "%.2f,"                   // Filt Alt
                "%.2f,%.2f,%.2f,"         // Est p (px, py, pz)
                "%.2f,%.2f,%.2f\n",       // Est v (sx, sy, sz)

                // Variables
                (unsigned long long)d.timestamp, 
                d.accel.ax, d.accel.ay, d.accel.az,
                d.lin_vel.vx, d.lin_vel.vy, d.lin_vel.vz,   
                d.ang_vel.gx, d.ang_vel.gy, d.ang_vel.gz,     
                d.mag.mx, d.mag.my, d.mag.mz,
                d.bulk_def.bulk_def_1, d.bulk_def.bulk_def_2, d.bulk_def.bulk_def_3,
                d.air_def.air_def_1, d.air_def.air_def_2, d.air_def.air_def_3, d.air_def.air_def_4,
                d.air_load.air_load_1, d.air_load.air_load_2, d.air_load.air_load_3, d.air_load.air_load_4,
                d.baro.pressure, d.baro.alt,
                d.temp.temp_1, d.temp.temp_2, d.temp.temp_3, d.temp.temp_4,
                d.audio.audio,                               
                d.filtered.accel_f[0], d.filtered.accel_f[1], d.filtered.accel_f[2], 
                d.filtered.gyro_f[0], d.filtered.gyro_f[1], d.filtered.gyro_f[2],    
                d.filtered.alt_f,
                d.estimated.px, d.estimated.py, d.estimated.pz, 
                d.estimated.sx, d.estimated.sy, d.estimated.sz  
            );
        }

        dataFile.close();

        bufferIndex = 0;
    }
}
