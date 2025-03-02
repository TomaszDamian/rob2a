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
void StopMotors(int stop_time){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	motor[crane] = 0;
	motor[claw] = 0;
	wait1Msec(stop_time);
}

void FullStopMotors(){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

//+++++++++++++++++++++++++++++++++++++++++| reset_encoder |+++++++++++++++++++++++++++++++++++++++++++
void reset_encoder(){
	SensorValue[RightQuadEncoder] = 0;	  // Set the encoder so that it starts counting at 0
	SensorValue[LeftQuadEncoder]  = 0;	  // Set the encoder so that it starts counting at 0
}

//+++++++++++++++++++++++++++++++++++++++++++++| drive |+++++++++++++++++++++++++++++++++++++++++++++++
void Drive(int dist, bool b_f){
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

void turn_giro(int degrees10,bool direction){
	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	reset_encoder();
  //Reconfigure Analog Port 7 as a Gyro sensor and allow time for ROBOTC to calibrate it
  SensorType[LeftQuadEncoder] = sensorGyro;
  wait1Msec(1500);

  while(abs(SensorValue[LeftQuadEncoder]) < degrees10)
  {
		if (direction){
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

//++++++++++++++++++++++++++++++++++++ DriveUsingController ++++++++++++++++++++++++++++++++++++++

task DriveUsingController(){
  int threshold = 10;   // helps to eliminate 'noise' from a joystick that isn't perfectly at (0,0)

  while(true)
  {
  	//left motor is controlled by the left joystick
  	if(abs(vexRT[Ch3]) >= threshold){
  		motor[leftMotor] = vexRT[Ch3];
  	}
  	else{
  		motor[leftMotor] = 0;
  	}

  	//right motor is controlled by the right joystick
  	if(abs(vexRT[Ch2]) >= threshold){
  		motor[rightMotor] = vexRT[Ch2];
  	}
  	else{
  		motor[rightMotor] = 0;
  	}

		//claw motors
    if(vexRT[Btn5U] == 1){
    	motor[claw] = 80;
   	}
   	else if(vexRT[Btn5D] == 1){
   		motor[claw] = -80;
   	}
   	else{
   		motor[claw] = 0;
   	}

		//arm motors
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

//++++++++++++++++++++++++++++++++++ driveForever +++++++++++++++++++++++++++++++++++++++++++++++
task driveForever(){
	while(true)
	{
		if(SensorValue(Light) < 200)
		{
			if(SensorValue(Sonar) > 40  || SensorValue(Sonar) == -1)
			{
				wait1Msec(200);
				motor[leftMotor] = 80;
				motor[rightMotor] = 80;
			}
			else
			{
				wait1Msec(200);
				motor[leftMotor] = -127;
				motor[rightMotor] = 127;
			}
		}
		else
		{
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
		}
	}
}
//++++++++++++++++++++++++++++++++++++ DriveUsingLineSensor ++++++++++++++++++++++++++++++++++++++
task DriveUsingLineSensor(){
	while(true){
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+
    //this is just a setup for the display to show the values							|
		//of the line sensors                                                 |
		displayLCDCenteredString(0, "LEFT  CNTR  RGHT");        //  Display   |
    displayLCDPos(1,0);                                     //  Sensor    |
    displayNextLCDNumber(SensorValue(LeftLineFollow));    //  Readings    |
    displayLCDPos(1,6);                                     //  to LCD.   |
    displayNextLCDNumber(SensorValue(CenterLineFollow));  //              |
    displayLCDPos(1,12);                                    //  L  C  R   |
    displayNextLCDNumber(SensorValue(RightLineFollow));   //  x  x  x     |
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+
		if(SensorValue(Sonar) > 10 || SensorValue(Sonar) == -1){
			//2800 black
			//2600 white
			if(SensorValue(CenterLineFollow) >= 2700){
					motor[rightMotor] = 60;
					motor[leftMotor] = 60;
			}
			if(SensorValue(RightLineFollow) < 2700){
					motor[rightMotor] = 90;
					motor[leftMotor] = 0;
			}
			if(SensorValue(LeftLineFollow) < 2700){
					motor[rightMotor] = 0;
					motor[leftMotor] = 90;
			}
		}
		else{
			FullStopMotors();
		}
	}
}
//++++++++++++++++++++++++++++++++++ EmergencyStop ++++++++++++++++++++++++++++++++++++++++++++

task EmergencyStop(){

	int RobotButtonBefore = 0;
	int RobotButtonStatus = 0;
	int ControllerButtonBefore = 0;
	int ControllerButtonStatus = 0;
	bool RobotStatus = true;

	while(true){
		RobotButtonStatus = SensorValue(BackButton);
		ControllerButtonStatus = vexRT[Btn8D];
		wait1Msec(5);
		if(RobotButtonStatus == 1 && RobotButtonBefore == 0){
			if(RobotStatus){
				StopTask(DriveUsingLineSensor);
				FullStopMotors();
				RobotStatus = false;
			}
			else{
				StartTask(DriveUsingLineSensor);
				RobotStatus = true;
			}
		}
		if(ControllerButtonStatus == 1 && ControllerButtonBefore == 0){
			if(RobotStatus){
				StopTask(DriveUsingLineSensor);
				FullStopMotors();
				RobotStatus = false;
			}
			else{
				StartTask(DriveUsingLineSensor);
				RobotStatus = true;
			}
		}
		RobotButtonBefore = RobotButtonStatus;
		ControllerButtonBefore = ControllerButtonStatus;
		wait1Msec(5);
	}
}

//++++++++++++++++++++++++++++++++++ Begin ++++++++++++++++++++++++++++++++++++++++++++
	void Begin(){
	//first you have to open the claw
	motor[crane] = 127;
	wait1Msec(40);
	motor[crane] = 0;

	//then you want to lift the crane
	motor[claw] = 127;
	wait1Msec(375);
	motor[claw] = 0;
}
//++++++++++++++++++++++++++++++++++ end ++++++++++++++++++++++++++++++++++++++++++++
void End(int dist){
	//int distance = dist * 10;
  //Turn(distance*2,true);
	//first you have to open the claw
	motor[crane] = -127;
	wait1Msec(40);
	motor[crane] = 0;

	//then you want to lift the crane
	motor[claw] = -127;
	wait1Msec(300);
	motor[claw] = 0;
}

void Claw_(bool b_f){
		int dir = (b_f)? (1):(-1);
		motor[claw] = 127* dir;
		wait1Msec(300);
		motor[claw] = 0*dir;
}
void Crane_(bool b_f){
		int dir = (b_f)? (1):(-1);
		motor[crane] = -127 * dir;
		wait1Msec(100);
		motor[crane] = 0 *dir;
}
//++++++++++++++++++++++++++++++++++ linesensorAndEncoder ++++++++++++++++++++++++++++++++++++++++++++
void DriveLineSensAndEncoder(int dist){
int distance = dist * 10;
	while(distance > abs(SensorValue[RightQuadEncoder]) && abs(SensorValue[LeftQuadEncoder]) < distance)		// Creates an infinite loop, since "true" always evaluates to true
	{
		if(SensorValue(CenterLineFollow) >= 2700){
					motor[rightMotor] = 60;
					motor[leftMotor] = 60;
			}
			if(SensorValue(RightLineFollow) < 2700){
					motor[rightMotor] = 90;
					motor[leftMotor] = 0;
			}
			if(SensorValue(LeftLineFollow) < 2700){
					motor[rightMotor] = 0;
					motor[leftMotor] = 90;
			}
	}
}

void verk6(){
	while(true){
			if(SensorValue(CenterLineFollow) >= 2700){
				motor[rightMotor] = 80;
				motor[leftMotor] = 80;
			}
			if(SensorValue(LeftLineFollow) > 2500){
				motor[rightMotor] = 80;
				motor[leftMotor] = -10;
			}
			if(SensorValue(RightLineFollow) > 2500){
				motor[leftMotor] = 80;
				motor[rightMotor] = -10;
			}
			if(SensorValue(CenterLineFollow) < 2400 && SensorValue(RightLineFollow) < 2400 && SensorValue(LeftLineFollow) < 2400){
				break;
			}
	}
}
//++++++++++++++++++++++++++++++++++ battery ++++++++++++++++++++++++++++++++++++++++++++
task battery(){
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
