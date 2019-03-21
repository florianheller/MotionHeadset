#include "MH_BLE.h"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


void setup_BLE() {
// Create the BLE Device
  BLEDevice::init("MotionHeadset");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the IMU BLE Service
  BLEService *pService = pServer->createService(UUID_SERVICE_IMU);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      UUID_CHAR_COMBOHPR,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
                    
  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor    2902 because we provide notifictions              
  pCharacteristic->addDescriptor(new BLE2902());
  BLEDescriptor *imuDescriptor = new BLEDescriptor(BLEUUID((uint16_t) 0x2901));
  imuDescriptor->setValue("IMU Data");
  pCharacteristic->addDescriptor(imuDescriptor);
  // TODO: add acceleration vector service, gyro vector service and magentometer vector service
  // Start the service
  pService->start();



  // Device info Service
  BLEService *infoService = pServer->createService(UUID_SERVICE_INFO);

  manufacturerCharacteristic = infoService->createCharacteristic(UUID_MANUFACTURER, BLECharacteristic::PROPERTY_READ);
  manufacturerCharacteristic->setValue(INFO_MANUFACTURER);
  modelnrCharacteristic = infoService->createCharacteristic(UUID_MODELNUMBER, BLECharacteristic::PROPERTY_READ);
  modelnrCharacteristic->setValue(INFO_MODELNUMBER);
  serialnrCharacteristic = infoService->createCharacteristic(UUID_SERIALNUMBER ,BLECharacteristic::PROPERTY_READ);
  serialnrCharacteristic->setValue(INFO_SERIALNUMBER);
  hwCharacteristic = infoService->createCharacteristic(UUID_HW_REV ,BLECharacteristic::PROPERTY_READ);
  hwCharacteristic->setValue(INFO_HW_REV);
  fwCharacteristic = infoService->createCharacteristic(UUID_FW_REV ,BLECharacteristic::PROPERTY_READ);
  fwCharacteristic->setValue(INFO_FW_REV);

  infoService->start();

    // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(UUID_SERVICE_IMU);
  pAdvertising->addServiceUUID(UUID_SERVICE_INFO);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  
}
