#include <ArduinoJson.h>

const int led_pin = 9;

//---------------------------------------

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Init done ...");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    String receiver = Serial.readStringUntil('\n');
    JsonDocument document;
    DeserializationError error = deserializeJson(document, receiver);
    if (error) {
      return;
    }
    String cmd = document["cmd"].as<String>();
    int brightness = document["data"].as<int>();
    if (cmd == "LIGHT") {
      brightness = constrain(brightness, 0, 255);
      analogWrite(led_pin, brightness);
    } else if (cmd == "OFF") {
      analogWrite(led_pin, 0);
    } 
  }
}
