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
I am trying to make this as flexible as possible. Right now I have an Adafruit Huzzah 32 Feather board and a Sparkfun Thing32 for testing. Both boards come with a LiPo charger, which makes them easy to integrate. 
The Thing32 can be extended using the Sparkfun Motion Shield that comes with an LSM9DS1 IMU, making it a nice, compact unit that can even be extended to include GPS if needed. 
I will also try the Bosch BNO055 IMU for comparison. 

