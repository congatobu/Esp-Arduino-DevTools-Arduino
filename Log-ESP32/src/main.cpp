#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial bluetoothSerial;

void TaskSendData(void *pvParameters)
{
  while (true)
  {
    Serial.println("gui du lieu len server");
    bluetoothSerial.println("{hello: 1}");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetoothSerial.begin("ESP32-BT");
  Serial.println("Bluetooth SPP start...");
  delay(5000);

 
  

  xTaskCreatePinnedToCore(TaskSendData, "Send Data ", 2000, NULL, 1, NULL, 1);
}

void loop()
{
  if (bluetoothSerial.available() > 0)
  {

    String data = bluetoothSerial.readStringUntil('\n');
    Serial.println(data);
  }

  if (bluetoothSerial.available()> 0)
  {
    char incomingChar = bluetoothSerial.read();
    Serial.write(incomingChar); // In dữ liệu nhận được ra Serial Monitor
  }

  if (Serial.available())
  {
    bluetoothSerial.write(Serial.read());
  }
}
