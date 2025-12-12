#include <Wire.h>

const byte MY_ADDR = 0x10;

// UPDATED PINS
const int RED_PIN   = 3;
const int GREEN_PIN = 4;

// 0 = RED, 1 = GREEN
volatile byte currentState = 0;

void applyState() {
  if (currentState == 0) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
  } else if (currentState == 1) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
  }
}

void onReceive(int numBytes) {
  if (numBytes >= 1) {
    currentState = Wire.read();
  }
  while (Wire.available()) Wire.read();
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  Wire.begin(MY_ADDR);
  Wire.onReceive(onReceive);
}

void loop() {
  applyState();
}