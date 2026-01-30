#pragma once

#include "constants.h"

void initIMU();
void initAltimeter();
void initTemperatureSensors();
void initBulkDefSensors();
void initAirDefSensors();
void initAirLoadSensors();
void initMicrophone();

void calibrateSensors();

void readSensors();



