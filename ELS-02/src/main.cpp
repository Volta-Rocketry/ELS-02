#include <Arduino.h>
#include "constants.h"
#include "sensors_manager.h"

StructGlobalData rocketData;

uint32_t PREVIOUS_MILLIS = 0;
uint32_t PREVIOUS_TELEMETRY = 0;
bool ledState = false;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("ELS-02 INITIALIZED");
  initIMU();
  initAltimeter();
  initTemperatureSensors();
  initBulkDefSensors();
  initAirDefSensors();
  initAirLoadSensors();
  initMicrophone();
}

void loop() {
  uint32_t currentMillis = millis();

  if (currentMillis - PREVIOUS_MILLIS > BLINK_MS) {
    PREVIOUS_MILLIS = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}
