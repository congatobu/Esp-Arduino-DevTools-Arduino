#include <SoftwareSerial.h>
#include "QMC5883L.h"
#include <Wire.h>

QMC5883L compass;


long send_data_time_out = 1000;
long send_data_time = 0;

long read_compass_sensor_time = 0;
long read_compass_sensor_time_out = 300;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {}

  compass.init();
  compass.setSamplingRate(50);

  Serial.println("QMC5883L Compass Demo");
  Serial.println("Turn compass in all directions to calibrate....");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
  }

 

  if (millis() >= read_compass_sensor_time + read_compass_sensor_time_out) {
    read_compass_sensor_time = read_compass_sensor_time + read_compass_sensor_time_out;
    int heading = compass.readHeading();
    Serial.println(heading);
  }
}
