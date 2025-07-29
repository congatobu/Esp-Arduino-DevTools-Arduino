#include <SoftwareSerial.h>
#include <Wire.h>
#include <ArduinoJson.h>

#define TX_PIN 4
#define RX_PIN 3

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

const int led_pin = 9;

//---------------------------------------

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {}

  bluetooth.begin(9600);

  Serial.println("Init done ...");
}

void loop() {
  // put your main code here, to run repeatedly:
  bluetooth_controller();
}



void bluetooth_controller() {
  if (bluetooth.available() > 0) {

    String bluetooth_receiver = bluetooth.readStringUntil('\n');

    JsonDocument document;

    DeserializationError error = deserializeJson(document, bluetooth_receiver);

    if (error) {
      Serial.println(bluetooth_receiver);
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

    Serial.println(bluetooth_receiver);
  }
}
