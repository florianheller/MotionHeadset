/* This class abstracts the IMU sensor logic and exposes one single unified interface
 *  
 *  TODOs: merge the Sparkfun and the Adafruit LSM9DS1 library to something that behaves like the BNO054 library
 *  */
#include "MH_IMU.h"
 
void setup_IMU() {
  
  /* Initialise the sensor */
  if(!mhIMU.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no IMU detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  setup_BNO();

}


/* The setup calls required for the BNO055 to work */
void setup_BNO() {
    mhIMU.setExtCrystalUse(true);
}


imu::Vector<3> getEuler() {

return mhIMU.getVector(Adafruit_BNO055::VECTOR_EULER);
        // TODO: Check if we can hand over the entire heading vector like this
        //pCharacteristic->setValue((uint8_t*)&euler, 6);
}
