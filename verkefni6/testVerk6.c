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
	//Begin();
	while(true){
		if(SensorValue(CenterLineFollow) > 2900 && SensorValue(RightLineFollow) > 2900 && SensorValue(LeftLineFollow) > 2900){
			FullStopMotors();
			break;
		}
		else if(SensorValue(CenterLineFollow) > 2900 || SensorValue(RightLineFollow) > 2900){
			motor[rightMotor] = 60;
			motor[leftMotor] = 80;
		}
		else if(SensorValue(CenterLineFollow) > 2900 || SensorValue(LeftLineFollow) > 2900){
			motor[rightMotor] = 80;
			motor[leftMotor] = 60;
		}
		else{
			motor[rightMotor] = 60;
			motor[leftMotor] = 60;
		}
	}
	wait1Msec(2000);

	while(true){
		motor[rightMotor] = 80;
		motor[leftMotor] = -40;
		wait1Msec(250);
		if(SensorValue(CenterLineFollow) > 2900){
			FullStopMotors();
			break;
		}
	}

/*	//when he's done picking up the item the crane should already be back in the air and the claw should be closed
	//then you want to turn 180 degrees and drive forward for half a meter
	Turn(TURNDIST*2, true);
	Drive(BASEDIST, true);

	//then you just want to repeat what you did above but in the opposite direction
	Turn(TURNDIST, false);
	Drive(BASEDIST, true);
	Turn(TURNDIST, true);
	StartTask(DriveUsingLineSensor);
	if(SensorValue(Sonar) < 15){
		StopTask(DriveUsingLineSensor);
		//set the crane back down as that is the initial position
		motor[crane] = -127;
		wait1Msec(5);
		motor[crane] = 0;
		wait10Msec(5);
		//opens the claw as that is the initial position
		motor[claw] = 127;
		wait1Msec(5);
		motor[claw] = 0;
	}*/
}
