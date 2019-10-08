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
|*                                         - Moving Forward -                                         *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs to move forward 0,5 meter and then back 0,5 meter and repeat it            *|
|*  0,5 meters more each time to 3 meters using basetime                                              *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Power levels that can be assigned to a motor port range from -127 (full reverse) to         *|
|*        127 (full forward).                                                                         *|
|*                                                                                                    *|
\*-----------------------------------------------------------------------------------------------4246-*/


#include "../Head/constNumber.h"

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);

	for(int counter = 1; counter < 5; counter++){
		DriveTime(BASETIME*counter,true);
		DriveTime(BASETIME*counter,false);
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
