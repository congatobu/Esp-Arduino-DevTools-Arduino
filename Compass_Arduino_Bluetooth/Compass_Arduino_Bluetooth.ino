#include <SoftwareSerial.h>
#include "QMC5883L.h"
#include <Wire.h>

#define TX_PIN 4
#define RX_PIN 3

QMC5883L compass;

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

long send_data_time_out = 1000;
long send_data_time = 0;

long read_compass_sensor_time = 0;
long read_compass_sensor_time_out = 300;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {}

  bluetooth.begin(9600);

  compass.init();
  compass.setSamplingRate(50);

  Serial.println("QMC5883L Compass Demo");
  Serial.println("Turn compass in all directions to calibrate....");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (bluetooth.available() > 0) {
    String data = bluetooth.readStringUntil('\n');
    //Serial.println(data);

    String cmd = data.substring(0,2);
    String value = data.substring(3,data.length());

    Serial.print(cmd);Serial.print("-");Serial.println(value);
  }

  if (millis() >= send_data_time + send_data_time_out) {
    send_data_time = send_data_time + send_data_time_out;
    // bluetooth.println("gui du lieu");
    //bluetooth.flush();
    //Serial.println("gui du lieu");
  }

  if (millis() >= read_compass_sensor_time + read_compass_sensor_time_out) {
    read_compass_sensor_time = read_compass_sensor_time + read_compass_sensor_time_out;
    int heading = compass.readHeading();
    Serial.println(heading);
    //send data
    bluetooth.println(heading);
  }
}
