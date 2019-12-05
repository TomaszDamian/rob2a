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
	part two of 4, this code is responsible for the fourth part of what is supposed to happen.
	This is supposed to drive towards ball 4
*/
#include "../Head/constNumber.h"

task main()
{
//turns function true = right | false = left

//crane down and claw closed is the initial position of the robot's arm
	//make sure to get it back to that position before you pass it into the next task

	//you start always by calling this
// 2200  <= white
// center 2500
// left and right 2400 ish
/*	Begin();
	verk6();*/
	claw_(false);
	Crane_(false);
	wait1Msec(1000);
	Turn(TURNDIST*1.6,true);
	Drive(15,true);
	verk6();
}
