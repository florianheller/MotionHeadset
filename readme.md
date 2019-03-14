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

	- Gyroscope x
	- Gyroscope y
	- Gyroscope z

### Orientation data
	- Orientation roll
	- Orientation pitch
	- Orientation yaw

	- Orientation as quaternion

### Other data
	- Temperature 


## Hardware
I am trying to make this as flexible as possible. Right now I have an [Adafruit Huzzah 32 Feather board](https://www.adafruit.com/product/3405) and a [Sparkfun Thing32](https://www.sparkfun.com/products/13907) for testing. Both boards come with a LiPo charger, which makes them easy to integrate. 
The Thing32 can be extended using the [Sparkfun ESP32 Motion Shield](https://www.sparkfun.com/products/14430) that comes with an LSM9DS1 IMU, making it a nice, compact unit that can even be extended to include GPS if needed. 
I will also use the [Bosch BNO055 IMU](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor) for comparison. 
There are Adafruit libraries for both IMUs [BNO055](https://github.com/adafruit/Adafruit_BNO055) and [LSM9DS1](https://github.com/adafruit/Adafruit_LSM9DS1). However, for the LSM9DS1, some calculations are necessary to generate a fused heading out of the raw sensor data. See [Sparkfun Library]((https://platformio.org/lib/show/1825/SparkFun%20LSM9DS1%20IMU)
## Bluetooth Details



