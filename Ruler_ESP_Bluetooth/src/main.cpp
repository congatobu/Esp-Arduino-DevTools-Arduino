#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>
#include <Adafruit_VL53L0X.h>

//------------------------------
#define I2C_SDA = 21
#define I2C_SCL = 22

Adafruit_VL53L0X VL53L0X = Adafruit_VL53L0X();

//------------------------------

BluetoothSerial bluetoothSerial;
//------------------------------
const int sensorPin = 34;

float distance = 0;

void TaskSendData(void *pvParameters)
{
  while (true)
  {
    // Serial.println("gui du lieu len server");

    JsonDocument document;

    document["d"] = distance;

    String out;

    serializeJson(document, out);

    bluetoothSerial.println(out);

    bluetoothSerial.flush();

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup()
{

  Serial.begin(9600);

  Wire.begin(SDA, SCL);

  if (!VL53L0X.begin())
  {

    Serial.println("Loi: Khong tim thay cam bien VL53L0X!");

    while ((1))
    {
    }

    Serial.println("VL53L0X da san sang");
  }
  else
  {

    Serial.println("VL53L0X da san sang");
  }

  bluetoothSerial.begin("ESP32-BT");

  Serial.println("Bluetooth SPP start...");

  delay(1000);

   xTaskCreatePinnedToCore(TaskSendData, "Send Data ", 2000, NULL, 1, NULL, 1);
}

String getRangeStatusString(uint8_t status)
{
  switch (status)
  {
  case 0:
    return "OK";
  case 1:
    return "Báo động";
  case 2:
    return "Out of range"; // Quá tầm đo
  case 4:
    return "Sigma thất bại"; // Sai số quá lớn
  case 5:
    return "Crosstalk thất bại"; // Tín hiệu nhiễu
  default:
    return "Không xác định";
  }
}

void read_vlox()
{

  VL53L0X_RangingMeasurementData_t rangingData;

  VL53L0X.rangingTest(&rangingData, false);

  if (rangingData.RangeStatus == VL53L0X_ERROR_NONE)
  {
    Serial.print("Distance (mm): ");

    distance = rangingData.RangeMilliMeter;
    Serial.println(distance);
  }
  else
  {
    Serial.print("Error: ");
    Serial.println(getRangeStatusString(rangingData.RangeStatus));
  }
  delay(100);
}



void loop()
{
  read_vlox();
  delay(100);
}