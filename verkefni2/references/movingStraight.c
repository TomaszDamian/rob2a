
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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*----------------------------------------------------------------------------------------------------*\
|*                                 - Moving Straight with Encoders -                                  *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program implements a self-straightening algorithm that provides a higher power level to the  *|
|*  motor that has traveled less, determined by comparing the values of the two encoders.             *|
|*  There is a 2 second pause at the beginning of the program.                                        *|
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

//#include "../headers/PortLayout.h"

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);							// Robot waits for 2000 milliseconds before executing program

	SensorValue[RightQuadEncoder] = 0;	  // Set the encoder so that it starts counting at 0
	SensorValue[LeftQuadEncoder]  = 0;	  // Set the encoder so that it starts counting at 0

	while(1 == 1)		// Creates an infinite loop, since "true" always evaluates to true
	{
		if(SensorValue[RightQuadEncoder] == SensorValue[LeftQuadEncoder]) // If rightEncoder has counted the same amount as leftEncoder:
		{
			// Move Forward
			motor[rightMotor] = -80;		    // Right Motor is run at power level 80
			motor[leftMotor]  = -80;		    // Left Motor is run at power level 80
		}
		else if(SensorValue[RightQuadEncoder] > SensorValue[LeftQuadEncoder])	// If rightEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[rightMotor] = -60;		    // Right Motor is run at power level 60
			motor[leftMotor]  = -80;		    // Left Motor is run at power level 80
		}
		else	// Only runs if leftEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[rightMotor] = -80;		    // Right Motor is run at power level 80
			motor[leftMotor]  = -60;		    // Left Motor is run at power level 60
		}
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
