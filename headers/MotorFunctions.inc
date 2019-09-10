/*void DriveTime(float Time, bool direction){
	if(direction){ MotorDirection = 127; }
	else{ MotorDirection = (-127); }
	motor[rightMotor] = MotorDirection;
	motor[leftMotor]  = MotorDirection;
	wait1Msec(Time);
}*/


//PI * diameter (PI * 10.5)
//cirucumference  = 33
//360 / 33
//distance per degree = 0.1
//the distance is always given in meters
int MotorDirection;
void DriveStraight(float distance, bool direction){
	SensorValue[RightQuadEncoder] = 0;	  // Set the encoder so that it starts counting at 0
	SensorValue[LeftQuadEncoder]  = 0;	  // Set the encoder so that it starts counting at 0
	if(direction){ MotorDirection = 1; }
	else { MotorDirection = -1; }
	float distanceInCM = distance*100;
	while(abs(SensorValue[RightQuadEncoder]*BASEDIST) <= distanceInCM && abs(SensorValue[LeftQuadEncoder]*BASEDIST) <= distanceInCM){
		if(SensorValue[RightQuadEncoder] == SensorValue[LeftQuadEncoder]) // If rightEncoder has counted the same amount as leftEncoder:
		{
			// Move Forward
			motor[rightMotor] = (80*MotorDirection);		    // Right Motor is run at power level 80
			motor[leftMotor]  = (80*MotorDirection);		    // Left Motor is run at power level 80
		}
		else if(SensorValue[RightQuadEncoder] > SensorValue[LeftQuadEncoder])	// If rightEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[rightMotor] = (60*MotorDirection);		    // Right Motor is run at power level 60
			motor[leftMotor]  = (80*MotorDirection);		    // Left Motor is run at power level 80
		}
		else	// Only runs if leftEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[rightMotor] = (80*MotorDirection);		    // Right Motor is run at power level 80
			motor[leftMotor]  = (60*MotorDirection);		    // Left Motor is run at power level 60
		}
	}
}

void StopMotors(int Time){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(Time);
}
