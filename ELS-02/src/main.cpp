#include <Arduino.h>
#include "constants.h"
#include "sensors_manager.h"

uint32_t previous_millis = 0;
uint32_t previous_telemetry = 0;
bool led_state = false;

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
  uint32_t current_millis = millis();

  if (current_millis - previous_millis > BLINK_MS) {
    previous_millis = current_millis;
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
  }
}
