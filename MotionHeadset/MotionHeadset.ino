#include "MH_IMU.h"
#include "MH_BLE.h"

bool shouldReadBattery = true;

void setup() {
  // For debug messages
  Serial.begin(115200);

  setup_IMU();

  setup_BLE();
  Serial.println("Waiting a client connection to notify...");
  readBattery();

}

void loop() {

  //Check wether we have a device connected, which means we have to read the data from the sensors
  if (deviceConnected) {
    
    imu::Vector<3> euler = mhIMU.getVector(Adafruit_BNO055::VECTOR_EULER);

    uint16_t x = euler.x();
    uint16_t y = euler.y();
    uint16_t z = euler.z();
    
    uint8_t value[] = {(x & 0xff), ((x >> 8) & 0xff), (z & 0xff), ((z >> 8) & 0xff), (y & 0xff), ((y >> 8) & 0xff), 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, (x & 0xff), ((x >> 8) & 0xff)};
    pCharacteristic->setValue(value, 14);
    pCharacteristic->notify();

    imu::Vector<3> magVector = mhIMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    uint16_t mx = magVector.x();
    uint16_t my = magVector.y();
    uint16_t mz = magVector.z();
    
    uint8_t magValue[] = {(mx & 0xff), ((mx >> 8) & 0xff), (my & 0xff), ((my >> 8) & 0xff), (mz & 0xff), ((mz >> 8) & 0xff)};
    magCharacteristic->setValue(magValue, 6);
    magCharacteristic->notify();


    imu::Vector<3> accVector = mhIMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    uint16_t ax = accVector.x();
    uint16_t ay = accVector.y();
    uint16_t az = accVector.z();
    
    uint8_t accValue[] = {(ax & 0xff), ((ax >> 8) & 0xff), (ay & 0xff), ((ay >> 8) & 0xff), (az & 0xff), ((az >> 8) & 0xff)};
    accCharacteristic->setValue(accValue, 6);
    accCharacteristic->notify();
    
    delay(IMU_SAMPLERATE_DELAY_MS); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
  }

  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
    delay(500); // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }


  // connecting
  if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
}

uint8_t readBattery() {
  //Read battery level from pin A13 and multiply by 2 (on the ESP32 Feather)
  //
  int batterySensing = analogRead(A13) * 2;
  // According to the docs, there is a voltage divider on A13 which means that we have to multiply the result by 2
  // Should be 8191 (12-bit ADC), but the max value at which the charger turns of is 4676
  // Normalize to 0-100
  uint8_t batteryLevel = (analogRead(A13) * 200) / 8191;
  Serial.println(batterySensing);
  Serial.println(batteryLevel);
  // Return a value between 0-100
  return batteryLevel;

}
