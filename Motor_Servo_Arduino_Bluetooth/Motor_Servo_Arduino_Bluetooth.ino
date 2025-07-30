#include <SoftwareSerial.h>
#include <Wire.h>
#include <ArduinoJson.h>
#define TX_PIN 4
#define RX_PIN 3

const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

long send_data_time_out = 1000;
long send_data_time = 0;

//---------------------------------------
long randomNumber;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {}

  bluetooth.begin(9600);
  Serial.println("Init done ...");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (bluetooth.available() > 0) {
    String data = bluetooth.readStringUntil('\n');
    Serial.println(data);
    processInput(data);
  }
}

void processInput(String jsonStr) {
  StaticJsonDocument<128> doc;
  DeserializationError error = deserializeJson(doc, jsonStr);

  if (error) {
    Serial.println("JSON Error");
    return;
  }

  String cmd = doc["cmd"];
  int data = doc["data"];

  if (cmd == "S1") {
    data = constrain(data, 0, 180);
    Serial.print("Set servo 1 to: ");
    Serial.println(data);
  }

  if (cmd == "S2") {
    data = constrain(data, 0, 180);
    Serial.print("Set servo 2 to: ");
    Serial.println(data);
  }


  if (cmd == "M1") {
    data = constrain(data, 0, 255);
    analogWrite(ENA, data);
    Serial.print("Set motor 1 speed to: ");
    Serial.println(data);
  }

  if (cmd == "M2") {
    data = constrain(data, 0, 255);
    analogWrite(ENA, data);
    Serial.print("Set motor 2 speed to: ");
    Serial.println(data);
  }
  if (cmd == "M3") {
    data = constrain(data, 0, 255);
    analogWrite(ENA, data);
    Serial.print("Set motor 3 speed to: ");
    Serial.println(data);
  }

  if (cmd == "M4") {
    data = constrain(data, 0, 255);
    analogWrite(ENA, data);
    Serial.print("Set motor 4 speed to: ");
    Serial.println(data);
  }
}
