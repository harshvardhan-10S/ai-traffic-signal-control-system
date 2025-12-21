#include <Wire.h>

const byte SLAVE1_ADDR = 0x10;
const byte SLAVE2_ADDR = 0x11;

const int MQ135_PIN = A0;

volatile int lane1_vehicles = 5;
volatile int lane2_vehicles = 5;

String serialBuffer = "";

void setup() {
  Serial.begin(115200);
  Wire.begin();  // master
}

// state: 0 = RED, 1 = GREEN
void sendState(byte addr, byte state) {
  Wire.beginTransmission(addr);
  Wire.write(state);
  Wire.endTransmission();
}

// Parse "D,x,y"
void handleSerialLine(const String &line) {
  if (line.length() == 0) return;
  if (line.charAt(0) != 'D') return;

  int c1 = line.indexOf(',');
  int c2 = line.indexOf(',', c1 + 1);
  if (c1 == -1 || c2 == -1) return;

  int v1 = line.substring(c1 + 1, c2).toInt();
  int v2 = line.substring(c2 + 1).toInt();

  if (v1 >= 0 && v2 >= 0) {
    lane1_vehicles = v1;
    lane2_vehicles = v2;
  }
}

void readSerialNonBlocking() {
  while (Serial.available() > 0) {
    char ch = Serial.read();
    if (ch == '\n' || ch == '\r') {
      handleSerialLine(serialBuffer);
      serialBuffer = "";
    } else {
      serialBuffer += ch;
      if (serialBuffer.length() > 50) {
        serialBuffer = "";
      }
    }
  }
}

void loop() {
  // 1) handle incoming density data
  readSerialNonBlocking();

  // 2) read MQ135 and send to Python
  int aq_raw = analogRead(MQ135_PIN);
  Serial.print("AQ,");
  Serial.println(aq_raw);

  // 3) simple timing logic based on density
  int baseGreen = 8000;          // 8 s
  int extraPerVehicle = 400;     // 0.4 s per extra vehicle

  int d1 = lane1_vehicles - lane2_vehicles;
  int d2 = lane2_vehicles - lane1_vehicles;
  if (d1 < 0) d1 = 0;
  if (d2 < 0) d2 = 0;

  unsigned long green1 = baseGreen + extraPerVehicle * d1;
  unsigned long green2 = baseGreen + extraPerVehicle * d2;

  if (green1 > 20000UL) green1 = 20000UL;
  if (green2 > 20000UL) green2 = 20000UL;

  // -------- PHASE 1: Lane1 GREEN, Lane2 RED --------
  sendState(SLAVE1_ADDR, 1); // Slave1 GREEN
  sendState(SLAVE2_ADDR, 0); // Slave2 RED
  delay(green1);

  // small all-RED gap if you want
  sendState(SLAVE1_ADDR, 0);
  sendState(SLAVE2_ADDR, 0);
  delay(2000);

  // -------- PHASE 2: Lane1 RED, Lane2 GREEN --------
  sendState(SLAVE1_ADDR, 0); // Slave1 RED
  sendState(SLAVE2_ADDR, 1); // Slave2 GREEN
  delay(green2);

  // small all-RED again
  sendState(SLAVE1_ADDR, 0);
  sendState(SLAVE2_ADDR, 0);
  delay(2000);
}
