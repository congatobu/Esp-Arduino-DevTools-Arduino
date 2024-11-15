#include <SoftwareSerial.h>
#include <Wire.h>
#include <ArduinoJson.h>

#include <NewPing.h>

#include <AFMotor.h>
#include <Servo.h>

#define TX_PIN 4 
#define RX_PIN 3


#define TRIGGER_PIN A0    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN A1       // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

Servo servo;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.

long send_data_time_out = 200;
long send_data_time = 0;


long heading = 0;
long distance = 200;

bool direction = true;

void setup() {

  Serial.begin(9600);

  Wire.begin();

  while (!Serial) {}

  bluetooth.begin(9600);

  servo.attach(10);

  Serial.println("Turn compass in all directions to calibrate....");
}

void loop() {
  // put your main code here, to run repeatedly:


  if (bluetooth.available() > 0) {
    String data = bluetooth.readStringUntil('\n');
    Serial.println(data);

    String cmd = data.substring(0, 2);
    String value = data.substring(3, data.length());

    Serial.print(cmd);
    Serial.print("-");
    Serial.println(value);
  }


  if (millis() >= send_data_time + send_data_time_out) {
    send_data_time = send_data_time + send_data_time_out;
    send_data_to_phone();

    servo.write(heading);
  }
}


void send_data_to_phone() {

  if (heading >= 180) {
    direction = false;
  }

  if (heading <= 0) {
    direction = true;
  }

  if (direction) {
    heading = heading + 2;
  } else {
    heading = heading - 2;
  }


  distance = sonar.ping_cm();  // Send ping, get distance in cm and print result (0 = outside set distance range)

  JsonDocument doc;

  doc["d"] = distance;

  doc["a"] = heading;


  String out;

  serializeJson(doc, out);

  Serial.println(out);
  //out += '\n';
  bluetooth.println(out);


  bluetooth.flush();

  // long end_time = millis();
  // long run_time = end_time - start_time;
  //Serial.println(run_time);
}
