
#ifndef BLE_HEADER
  #define BLE_HEADER
  

  #include <BLEDevice.h>
  #include <BLEServer.h>
  #include <BLEUtils.h>
  #include <BLE2902.h>

  #define UUID_SERVICE_IMU "7ca251df-137b-41b2-9169-1c0215bea6de"
  #define UUID_CHAR_COMBOHPR "919d5add-298f-4431-acf9-9f67275f1455"
  #define UUID_CHAR_ACCVECTOR = "e1f1e3bd-9672-4213-948d-206c4fa9820f"
  #define UUID_CHAR_MAGVECTOR = "32d9c336-722b-4ec5-998f-4f7dcf08f465"
  #define UUID_CHAR_MAGCALDATA = "ad6486a9-bceb-4ebd-9ca3-48b9a9675be5"
  #define UUID_CHAR_GEOMAGPARAMS = "760d93e8-476d-4d7c-a894-b95112d16aea"
  #define UUID_CHAR_MAGDISTPARAMS = "e08b0483-63eb-4920-86d5-c1e2b5ae6e72"
  #define UUID_SERVICE_GPS = "52466e96-a001-425a-96b6-7d5795a1ea08"
  
  BLEServer* pServer = NULL;
  BLECharacteristic* pCharacteristic = NULL;
  
  bool deviceConnected = false;
  bool oldDeviceConnected = false;
  
  bool headingConnected = false;
  bool oldHeadingConnected = false;
  
  bool aConnected = false;
  bool oldAConnected = false;
  
  bool mConnected = false;
  bool oldMConnected = false;
  
  void setup_BLE();

#endif
