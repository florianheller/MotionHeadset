/* This class abstracts the IMU sensor logic and exposes one single unified interface
 *  
 *  TODOs: merge the Sparkfun and the Adafruit LSM9DS1 library to something that behaves like the BNO054 library
 *  */
/* Define which type of sensor you are using here */

#define BNO055


#ifndef IMU_HEADER
#define IMU_HEADER
  /* Set the delay between fresh samples */
  #define IMU_SAMPLERATE_DELAY_MS (10)

  #include <Wire.h>
  #include <Adafruit_Sensor.h>

  #include <Adafruit_BNO055.h>
  #include <utility/imumaths.h>    
  
  Adafruit_BNO055 mhIMU = Adafruit_BNO055();
  
  imu::Vector<3> getEuler();

#endif
