#include <SoftwareSerial.h>
#include <Wire.h>
#include <ArduinoJson.h>

#define TX_PIN 4
#define RX_PIN 3

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

long send_data_time_out = 500;
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

  bluetooth_controller();

  if (millis() >= send_data_time + send_data_time_out) {
    send_data_time = send_data_time + send_data_time_out;
  }

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

    String command = document["cmd"];

    
    Serial.println(bluetooth_receiver);
  }
}
