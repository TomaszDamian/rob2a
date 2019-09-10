int MotorDirection;
void DriveTime(float Time, bool direction){
	if(direction){ MotorDirection = 127; }
	else{ MotorDirection = (-127); }
	motor[rightMotor] = MotorDirection;
	motor[leftMotor]  = MotorDirection;
	wait1Msec(Time);
}
