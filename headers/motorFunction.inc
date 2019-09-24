//PI * diameter (PI * 10.5)
//cirucumference  = 33 drivedist number

//+++++++++++++++++++++++++++++++++++++++++| stopMotor |+++++++++++++++++++++++++++++++++++++++++++
void StopMotors(int sop_time){
	motor[leftMotor]=0;
	motor[rightMotor]=0;
	wait1Msec(sop_time);
}

//+++++++++++++++++++++++++++++++++++++++++| reset_encoder |+++++++++++++++++++++++++++++++++++++++++++
void reset_encoder(){
	SensorValue[RightQuadEncoder] = 0;	  // Set the encoder so that it starts counting at 0
	SensorValue[LeftQuadEncoder]  = 0;	  // Set the encoder so that it starts counting at 0
}

//+++++++++++++++++++++++++++++++++++++++++++++| drive |+++++++++++++++++++++++++++++++++++++++++++++++
void drive(int dist, bool b_f){				// Robot waits for 2000 milliseconds before executing program
	// returnar true = 1 | false = -1
	reset_encoder();
	int dir = (b_f)? (1):(-1);
	int distance = dist * 10;
	while(distance > abs(SensorValue[RightQuadEncoder]) || abs(SensorValue[LeftQuadEncoder]) < distance)		// Creates an infinite loop, since "true" always evaluates to true
	{
		if(SensorValue[RightQuadEncoder] == SensorValue[LeftQuadEncoder]) // If RightQuadEncoder has counted the same amount as LeftQuadEncoder:
		{
			// Move Forward
			motor[rightMotor] = (80 * dir);		    // Right Motor is run at power level 80
			motor[leftMotor]  = (80* dir);		    // Left Motor is run at power level 80
		}
		else if(SensorValue[RightQuadEncoder] > SensorValue[LeftQuadEncoder])	// If RightQuadEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[rightMotor] = (60* dir);		    // Right Motor is run at power level 60
			motor[leftMotor]  = (80* dir);		    // Left Motor is run at power level 80
		}
		else	// Only runs if LeftQuadEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[rightMotor] = (80* dir);		    // Right Motor is run at power level 80
			motor[leftMotor]  = (60* dir);		    // Left Motor is run at power level 60
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++| turns |++++++++++++++++++++++++++++++++++++++++++++++
void Turn(int dist, int turns)
{
	reset_encoder();

	while(abs(SensorValue[RightQuadEncoder]) < dist || abs(SensorValue[LeftQuadEncoder]) < dist) // While the right encoder is less than distance:
	{
		if(turns == 1){
			if(abs(SensorValue[RightQuadEncoder]) == abs(SensorValue[LeftQuadEncoder])){
			motor[rightMotor] = -80;         /* Run both motors        */
			motor[leftMotor]  = 80;         /* forward at half speed. */
			}
			else if(abs(SensorValue[RightQuadEncoder]) > abs(SensorValue[LeftQuadEncoder])){
				motor[rightMotor] = -60;
				motor[leftMotor] = 80;
			}
			else{
				motor[rightMotor] = -80;
				motor[leftMotor] = 60;
			}
		}
		else {
			if(abs(SensorValue[RightQuadEncoder]) == abs(SensorValue[LeftQuadEncoder])){
			motor[rightMotor] = 80;         /* Run both motors        */
			motor[leftMotor]  = -80;         /* forward at half speed. */
			}
			else if(abs(SensorValue[RightQuadEncoder]) > abs(SensorValue[LeftQuadEncoder])){
				motor[rightMotor] = 60;
				motor[leftMotor] = -80;
			}
			else{
				motor[rightMotor] = 80;
				motor[leftMotor] = -60;
			}
		}
	}
		motor[rightMotor] = 0;            /* Stop the motors once desired */
		motor[leftMotor]  = 0; 						/* distance has been reached.   */
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
