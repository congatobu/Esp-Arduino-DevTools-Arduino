#include <SoftwareSerial.h>
#include <Wire.h>

#define TX_PIN 4
#define RX_PIN 3

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

long send_data_time_out = 1000;
long send_data_time = 0;
const int ledPin = 9;  // Dùng PWM chân 9

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
    handleCommand(data);
  }
}

void handleCommand(String command) {
  command.trim();
  Serial.print("Command received: [");
  Serial.print(command);
  Serial.println("]");

  if (command.equalsIgnoreCase("HELLO")) {
    bluetooth.println("hello command");
  } else if (command.equalsIgnoreCase("ON")) {
    digitalWrite(ledPin, HIGH);
    bluetooth.println("{\"status\":\"LED ON\"}");
  } else if (command.equalsIgnoreCase("OFF")) {
    digitalWrite(ledPin, LOW);
    bluetooth.println("{\"status\":\"LED OFF\"}");
  } else if (command.equalsIgnoreCase("STATUS")) {
    int state = digitalRead(ledPin);
    bluetooth.print("{\"status\":\"LED ");
    bluetooth.print(state == HIGH ? "ON" : "OFF");
    bluetooth.println("\"}");
  } else if (command.substring(0, 3).equalsIgnoreCase("SET")) {
    String valueStr = command.substring(3);
    valueStr.trim();  // Loại bỏ khoảng trắng dư
    int brightness = valueStr.toInt();
    brightness = constrain(brightness, 0, 255);
    analogWrite(ledPin, brightness);
    bluetooth.print("{\"brightness\":");
    bluetooth.print(brightness);
    bluetooth.println("}");
  } else {
    Serial.println("sao lai vao day");
    bluetooth.println("{\"error\":\"Unknown command\"}");
  }
}
