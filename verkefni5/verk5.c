#pragma config(Sensor, in1,    Potient,        sensorPotentiometer)
#pragma config(Sensor, in2,    Light,          sensorReflection)
#pragma config(Sensor, in3,    Gyro,           sensorGyro)
#pragma config(Sensor, in4,    CenterLineFollow, sensorLineFollower)
#pragma config(Sensor, in5,    RightLineFollow, sensorLineFollower)
#pragma config(Sensor, in6,    LeftLineFollow, sensorLineFollower)
#pragma config(Sensor, dgtl1,  Sonar,          sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  LeftQuadEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  RightQuadEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  BackButton,     sensorTouch)
#pragma config(Sensor, dgtl8,  FrontButton,    sensorTouch)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port5,           crane,         tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port6,           claw,          tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
				This code is for the robot to follow a certain line on the ground.
				In this case it's a black line on a white surface,
				it also stops if it sees an item 10 cm in front of it.
				The lower the number the darker the surface.

*/

#include "../Head/constNumber.h"

task main()
{
	StartTask(EmergencyStop);
	StartTask(DriveUsingLineSensor);

	while(true){/*must run*/};

}
