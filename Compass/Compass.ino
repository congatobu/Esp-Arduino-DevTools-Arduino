#include <SoftwareSerial.h>
#include "QMC5883L.h"
#include <Wire.h>

#define TX_PIN 4
#define RX_PIN 3

QMC5883L compass;

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

long send_data_time_out = 1000;
long send_data_time = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {}


  bluetooth.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

  if (bluetooth.available()>0) {
    String data = bluetooth.readString();
    Serial.println(data);
  }

  if (millis() >= send_data_time + send_data_time_out) {
    send_data_time = send_data_time + send_data_time_out;
   // bluetooth.println("gui du lieu");
    //bluetooth.flush();
    //Serial.println("gui du lieu");
  }

 

}
