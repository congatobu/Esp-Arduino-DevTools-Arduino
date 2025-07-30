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

  if (cmd == "SA-ON") {
    Serial.println("Set SA-ON");
  }

  if (cmd == "SA-OFF") {
    Serial.println("Set SA-OFF");
  }


  if (cmd == "SB-ON") {
    Serial.println("Set SB-ON");
  }

  if (cmd == "SB-OFF") {
    Serial.println("Set SB-OFF");
  }

  if (cmd == "FA-ON") {
    Serial.println("Set FA-ON");
  }

  if (cmd == "FA-OFF") {
    Serial.println("Set FA-OFF");
  }

  if (cmd == "FB-ON") {
    Serial.println("Set FB-ON");
  }

  if (cmd == "FB-OFF") {
    Serial.println("Set FB-OFF");
  }

  if (cmd == "1-ON") {
    Serial.println("Set 1-ON");
  }

  if (cmd == "1-OFF") {
    Serial.println("Set 1-OFF");
  }

  if (cmd == "2-ON") {
    Serial.println("Set 2-ON");
  }

  if (cmd == "2-OFF") {
    Serial.println("Set 2-OFF");
  }

  if (cmd == "3-ON") {
    Serial.println("Set 3-ON");
  }

  if (cmd == "3-OFF") {
    Serial.println("Set 3-OFF");
  }

  if (cmd == "4-ON") {
    Serial.println("Set 4-ON");
  }

  if (cmd == "4-OFF") {
    Serial.println("Set 4-OFF");
  }

  if (cmd == "A-ON") {
    Serial.println("Set A-ON");
  }

  if (cmd == "A-OFF") {
    Serial.println("Set A-OFF");
  }

  if (cmd == "B-ON") {
    Serial.println("Set B-ON");
  }

  if (cmd == "B-OFF") {
    Serial.println("Set B-OFF");
  }

  if (cmd == "C-ON") {
    Serial.println("Set C-ON");
  }

  if (cmd == "C-OFF") {
    Serial.println("Set C-OFF");
  }

  if (cmd == "D-ON") {
    Serial.println("Set D-ON");
  }

  if (cmd == "D-OFF") {
    Serial.println("Set D-OFF");
  }

  //--------------------------------------
  if (cmd == "JR") {
    float x = doc["x"];
    float y = doc["y"];
    joystickRight(x, y);
  }

  if (cmd == "JL") {
    float x = doc["x"];
    float y = doc["y"];
    joystickLeft(x, y);
  }

  if (cmd == "LT") {
    turnLeft();  // quay đầu sang trái
  } else if (cmd == "LTL") {
    slightLeft();  // hơi lệch trái
  } else if (cmd == "LL") {
    moveLeft();  // di chuyển trái
  } else if (cmd == "LBL") {
    backLeft();  // lùi trái
  } else if (cmd == "LB") {
    moveBackward();  // lùi
  } else if (cmd == "LBR") {
    backRight();  // lùi phải
  } else if (cmd == "LR") {
    moveRight();  // di chuyển phải
  } else if (cmd == "LTR") {
    slightRight();  // hơi lệch phải
  } else if (cmd == "RT") {
    turnRight();  // quay đầu phải
  } else if (cmd == "RTL") {
    slightLeft();  // giống trái
  } else if (cmd == "RL") {
    moveLeft();
  } else if (cmd == "RBL") {
    backLeft();
  } else if (cmd == "RB") {
    moveBackward();
  } else if (cmd == "RBR") {
    backRight();
  } else if (cmd == "RR") {
    moveRight();
  } else if (cmd == "RTR") {
    slightRight();
  } else {
    stopMotors();  // không lệnh rõ ràng thì dừng
  }
}

void joystickRight(float x, float y) {
  Serial.print("joystick: x = ");
  Serial.print(x);
  Serial.print("; y = ");
  Serial.println(y);
}

void joystickLeft(float x, float y) {
  Serial.print("joystick: x = ");
  Serial.print(x);
  Serial.print("; y = ");
  Serial.println(y);
}

void moveForward() {
}

void moveBackward() {
}

void turnLeft() {
}

void turnRight() {
}

void moveLeft() {
}

void moveRight() {
}

void backLeft() {
}

void backRight() {
}

void slightLeft() {
}

void slightRight() {
}

void stopMotors() {
}