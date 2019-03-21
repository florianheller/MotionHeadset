#include "MH_IMU.h"
#include "MH_BLE.h"


void setup() {
  // For debug messages
  Serial.begin(115200);

  setup_IMU();

  setup_BLE();
  Serial.println("Waiting a client connection to notify...");

}

void loop() {
  
    //Check wether we have a device connected, which means we have to read the data from the sensors
    if (deviceConnected) {
       imu::Vector<3> euler = getEuler();
       uint16_t x = euler.x();
       uint8_t value[] = {(x & 0xff), ((x>>8) & 0xff), 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E};
       pCharacteristic->setValue(value, 14);
       pCharacteristic->notify();
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

int readBattery() {
  //Read battery level from pin A13 and multiply by 2 (on the ESP32 Feather)
  // Return a value between 0-100
  return 100;
  
}
