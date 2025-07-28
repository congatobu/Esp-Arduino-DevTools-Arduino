#define TRIG_PIN 9
#define ECHO_PIN 10

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Gửi xung 10 micro giây
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Đọc thời gian Echo
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Tính khoảng cách (cm)
  float distance = duration * 0.0343 / 2;

  // In kết quả
  
  Serial.println("{\"d\":" + String(distance) + "}");


  delay(500);
}
