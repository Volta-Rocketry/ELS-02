#include <Arduino.h>
#include "telemetry_structures.h"

global_data rocket_state;

int led_pin= 2; 
int blink= 500;
int previous_millis = 0;
bool led_state = false;

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  Serial.println("ELS-02 INITIALIZED");
}

void loop() {
  rocket_state.timestamp = micros();
  int current_millis = millis();

  if (current_millis - previous_millis > blink) {
    previous_millis = current_millis;
    led_state = !led_state;
    digitalWrite(led_pin, led_state);
  }
}
