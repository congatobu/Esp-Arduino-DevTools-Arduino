#include <SoftwareSerial.h>
#include <Wire.h>

#define TX_PIN 4
#define RX_PIN 3

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

const int ledPin = 13;

//---------------------------------------
long randomNumber;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {}

  bluetooth.begin(9600);
  pinMode(ledPin, OUTPUT); 

	Serial.println("Init done ...");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (bluetooth.available()>0) {
    String data = bluetooth.readStringUntil('\n');
    Serial.println(data);
    digitalWrite(ledPin, HIGH); 
    delay(100);
  }
  digitalWrite(ledPin, LOW);  
}
