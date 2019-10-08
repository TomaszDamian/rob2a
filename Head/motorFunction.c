//PI * diameter (PI * 10.5)
//cirucumference  = 33 drivedist number
//++++++++++++++++++++++++++++++++++++++++| Drive_time |+++++++++++++++++++++++++++++++++++++++++++
void drive_time(int drive_time,bool b_f){
	int dir = (b_f)? (1):(-1);
	motor[rightMotor] = dir*127;
	motor[leftMotor]  = dir*127;
	wait1Msec(drive_time);
}
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
void Drive(int dist, bool b_f){				// Robot waits for 2000 milliseconds before executing program
	// returnar true = 1 | false = -1
	reset_encoder();
int dir = (b_f)? (1):(-1);
	int distance = dist * 10;
	while(distance > abs(SensorValue[RightQuadEncoder]) && abs(SensorValue[LeftQuadEncoder]) < distance)		// Creates an infinite loop, since "true" always evaluates to true
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
			motor[rightMotor] = -80;         /* Run both motors        */
			motor[leftMotor]  = 80;         /* forward at half speed. */
		}
		else {
			motor[rightMotor] = 80;         /* Run both motors        */
			motor[leftMotor]  = -80;         /* forward at half speed. */
		}
	}
		motor[rightMotor] = 0;            /* Stop the motors once desired */
		motor[leftMotor]  = 0; 						/* distance has been reached.   */
}

//+++++++++++++++++++++++++++++++++++++++++++++| turn_Giro |++++++++++++++++++++++++++++++++++++++++++++++

void turn_giro(int degrees10,bool counterclock){
	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	reset_encoder();
  //Reconfigure Analog Port 7 as a Gyro sensor and allow time for ROBOTC to calibrate it
  SensorType[LeftQuadEncoder] = sensorGyro;
  wait1Msec(1500);

  while(abs(SensorValue[LeftQuadEncoder]) < degrees10)
  {
		if (counterclock){
		motor[rightMotor] = 80;
		motor[leftMotor] = -80;
		}
		else{
		motor[rightMotor] = -80;
		motor[leftMotor] = 80;
		}
  }

  //Brief brake to stop some drift
  motor[rightMotor] = -5;
  motor[leftMotor] = 5;
  wait1Msec(250);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

task DriveUsingController(){
	int joy_x;            // will hold the X value of the analog stick (choices below)
  int joy_y;            // will hold the Y value of the analog stick (choices below)
  int threshold = 15;   // helps to eliminate 'noise' from a joystick that isn't perfectly at (0,0)

  while((SensorValue[FrontButton] != 1) && (SensorValue[BackButton] != 1) && (vexRT[Btn8D] != 1))
  {
    joy_x = vexRT[Ch1];   // This is the RIGHT analog stick.  For LEFT, change 'Ch1' to 'Ch4'.
    joy_y = vexRT[Ch2];   // This is the RIGHT analog stick.  For LEFT, change 'Ch2' to 'Ch3'.

    // Forward, and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE)
    if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y > 0))
    {
      motor[leftMotor]  = (joy_y + joy_x)/2;
      motor[rightMotor] = (joy_y - joy_x)/2;
    }
    // Backwards and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE)
    else if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y < 0))
    {
      motor[leftMotor]  = (joy_y - joy_x)/2;
      motor[rightMotor] = (joy_y + joy_x)/2;
    }
    // Turning in place: (abs(X) is above the threshold, abs(Y) is below the threshold)
    else if((abs(joy_x) > threshold) && (abs(joy_y) < threshold))
    {
      motor[leftMotor]  = joy_x;
      motor[rightMotor] = (-1 * joy_x);
    }
    // Standing still: (both abs(X) and abs(Y) are below the threshold)
    else
    {
      motor[leftMotor]  = 0;
      motor[rightMotor] = 0;
    }


    if(vexRT[Btn5U] == 1){
    	motor[claw] = 80;
   	}
   	else if(vexRT[Btn5D] == 1){
   		motor[claw] = -80;
   	}
   	else{
   		motor[claw] = 0;
   	}


   	if((vexRT[Btn6U] == 1) && (SensorValue[Potient] > 0)){
   		motor[crane] = 80;
   	}
   	else if(vexRT[Btn6D] == 1 && (SensorValue[Potient] < 850) ){
   		motor[crane] = -80;
   	}
   	else{
   		motor[crane] = 0;
   	}
  }
}
