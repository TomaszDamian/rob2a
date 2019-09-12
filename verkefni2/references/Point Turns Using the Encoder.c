#pragma config(Sensor, in1,    Potient,        sensorPotentiometer)
#pragma config(Sensor, in2,    Light,          sensorReflection)
#pragma config(Sensor, in3,    Gyro,           sensorGyro)
#pragma config(Sensor, in4,    RightLineFollow, sensorLineFollower)
#pragma config(Sensor, in5,    CenterLineFollow, sensorLineFollower)
#pragma config(Sensor, in6,    LeftLineFollow, sensorLineFollower)
#pragma config(Sensor, dgtl1,  SonarIn,        sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  LeftQuadEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  RightQuadEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  BackButton,     sensorTouch)
#pragma config(Sensor, dgtl8,  FrontButton,    sensorTouch)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex269, openLoop)

/*----------------------------------------------------------------------------------------------------*\
|*                                   - Point Turns with Encoders -                                    *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to turn left, and then right, using feedback from the encoders   *|
|*  to determine how much.  There is a 2 second pause at the beginning of the program.                *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" model, but may not be needed for all robot configurations.                      *|
|*    2)  Whichever encoder is being used for feedback should be cleared just before it starts        *|
|*        counting by using the "SensorValue(encoder) = 0;".  This helps ensure consistancy.          *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 1,2  rightEncoder        VEX Shaft Encoder     Right side                        *|
|*    Digital - Port 3,4  leftEncoder         VEX Shaft Encoder     Left side                         *|
\*----------------------------------------------------------------------------------------------------*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);							            //Robot waits for 2000 milliseconds before executing program


	SensorValue[RightQuadEncoder] = 0;	          //Set the encoder so that it starts counting at 0

  while(abs(SensorValue(RightQuadEncoder)) <= 360)   //While rightEncoder has counted less than 1800 counts
	{
		//Turn Left
		motor[rightMotor] = 63;					      //Motor on port2 is run at full (127) power forward
		motor[leftMotor]  = -63;				        //Motor on port3 is run at full (-127) power reverse
	}

	SensorValue[LeftQuadEncoder] = 0;	            //Set the encoder so that it starts counting at 0

  while(abs(SensorValue(LeftQuadEncoder)) < 360)    //While leftEncoder has counted less than 1800 counts
	{
		//Turn Right
		motor[rightMotor] = -63;				        //Motor on port2 is run at full (-127) power reverse
		motor[leftMotor]  = 63;				      	//Motor on port3 is run at full (127) power forward
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
