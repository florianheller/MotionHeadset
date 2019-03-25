# MotionHeadset
## Get head orientation from your headphones for an immersive spatial audio experience

I'm doing research on audio agumented reality and spatial audio. With this technology you can place virtual sound sources in the physical space such that they are oerceived as being at fixed locations. For example, you could make a statue talk.
For this kind of application, you need two pieces of information: the user location and the user's head orientation. Location can easily be taken from the user's smartphone. The orientation information could also be taken from the smartphone with little impact on the experience, but for full immersion you need the head orientation. 
Unfortunately, Jabra has discontinued its Intelligent Headset (IHS) which I used in many experiments. Without software support, it is increasingly difficult to use it with modern versions of iOS and Android. 

## Features
The system should communicate the following information to the host

### RAW sensor data:
	- Accelerometer x
	- Accelerometer y
	- Accelerometer z

	- Magnetometer x
	- Magnetometer y
	- Magnetometer z

	- Gyroscope x (TODO)
	- Gyroscope y (TODO)
	- Gyroscope z (TODO)

### Orientation data
	- Orientation roll
	- Orientation pitch
	- Orientation yaw

	- Orientation as quaternion (TODO)

### Other data
	- Temperature 


## Hardware
I am trying to make this as flexible as possible. Right now I have an [Adafruit Huzzah 32 Feather board](https://www.adafruit.com/product/3405) and a [Sparkfun Thing32](https://www.sparkfun.com/products/13907) for testing. Both boards come with a LiPo charger, which makes them easy to integrate. 
The Thing32 can be extended using the [Sparkfun ESP32 Motion Shield](https://www.sparkfun.com/products/14430) that comes with an LSM9DS1 IMU, making it a nice, compact unit that can even be extended to include GPS if needed. 
I will also use the [Bosch BNO055 IMU](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor) for comparison. 
There are Adafruit libraries for both IMUs [BNO055](https://github.com/adafruit/Adafruit_BNO055) and [LSM9DS1](https://github.com/adafruit/Adafruit_LSM9DS1). However, for the LSM9DS1, some calculations are necessary to generate a fused heading out of the raw sensor data. See [Sparkfun Library](https://platformio.org/lib/show/1825/SparkFun%20LSM9DS1%20IMU)

## Bluetooth Details

The sensor data is sent to the clients using different characteristics. This should minimize the amount of data transmitted. In the case the spatial rendering algorithm does not simulate any elevation, only the heading information is relevant. 

### IMU Data Service: 
The IMU data service has the UUID 7ca251df-137b-41b2-9169-1c0215bea6de and provides the following characteristics, all of which support notifications:

- Heading Information Vector: 
	UUID "919d5add-298f-4431-acf9-9f67275f1455"
	The structure of this vector is based on the one used by the Jabra Intelligent Headset in order to create compatibility. However, this might be changed if it requires to many compromises to integrate the data from modern IMUs. 
	It provides 14 bytes of data:

	| Byte | Content           |
	| ---- | ----------------- |
	| 0	   | Fused Heading LSB |
	| 1    | Fused Heading MSB |
	| 2    | Pitch LSB         |
	| 3    | Pitch MSB         |
	| 4    | Roll LSB          |
	| 5    | Roll MSB          |
	| 6    | 0x07              |
	| 7    | 0x08              |
	| 6    | 0x09              |
	| 8    | 0x0A              |
	| 9    | 0x0B              |
	|10    | 0x0C              |
	|11    | Heading LSB       |
	|12    | Heading MSB       |

	The original IHS made a differentiation between heading and fused heading in the sense that heading was from the magnetometer only, whereas fused heading included the gyro. I don't think this differentiation is necessary with a good 9-DOF fusion algorithm. Currently, fused heading and heading contain the same info. 

- Accelerometer Data Vector:
	UUID e1f1e3bd-9672-4213-948d-206c4fa9820f
	Provides 6 bytes of data: ax LSB, ax MSB, ay LSB, ay MSB, az LSB, az MSB. All values in g.
- Magnetometer Data Vector: 
	UUID 32d9c336-722b-4ec5-998f-4f7dcf08f465
	Provides 6 bytes of data: mx LSB, mx MSB, my LSB, my MSB, mz LSB, mz MSB. All values in microTesla.

### System Information Service:
	Provides the following information
	- Manufacturer: "Motion Headset"
	- Model Number: "MH001"
	- Serial Number: "0001"
	- Hardware Revision: "1.0.0"
	- Firmware Revision: "1.0.0"

### Environmental Service
	Provides the information from the temperature sensor in the IMU. 

### Battery Service
	Provides the battery level as a value between 0 and 100. 
	This works if the ESP32 board provides the functionality such as on the one from Adafruit. The Sparkfun ESP32 Thing does not have the necessary connections. 

## TODOs:
	- OTA Updates?
	- Abstraction of IMUs to allow different types



