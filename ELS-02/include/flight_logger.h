#ifndef FLIGHTLOGGER_H
#define FLIGHTLOGGER_H

#include <Arduino.h>       
#include <SPI.h>           
#include <SD.h>            
#include "telemetry_structures.h" 

#define BUFFER_SIZE 100 

class FlightLogger {
public:
    // Pin connected to the SD
    FlightLogger(int csPin);

    // Start the hardware
    bool begin();

    // Save data
    void logGlobalState(global_data newData);

    // Force save (post-flight)
    void flush();

private:
    
    int chipSelect;     // Pin number
    int bufferIndex;    // Amount of accumulated data
    
    // Buffer
    global_data ramBuffer[BUFFER_SIZE]; 
};

#endif
