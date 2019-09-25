#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, in4,    lightsensor,    sensorReflection)
#pragma config(Sensor, in5,    Potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  bumper,         sensorTouch)
#pragma config(Sensor, dgtl6,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           Armmotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           Clawmotor,     tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|* - Moving using encoders through maze - *|
|* ROBOTC on VEX 2.0 CORTEX *|
|* *|
|* This program instructs your robot to move forward at full power for three seconds. There is a *|
|* two second pause at the beginning of the program. *|
|* *|
|* ROBOT CONFIGURATION *|
|* NOTES: *|
|* 1) Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the *|
|* "Squarebot" mode, but may not be needed for all robot configurations. *|
|* 2) Power levels that can be assigned to a motor port range from -127 (full reverse) to *|
|* 127 (full forward). *|
|* *|
|* MOTORS & SENSORS: *|
|* [I/O Port] [Name] [Type] [Description] *|
|* Motor Port 2 rightMotor VEX 3-wire module Right side motor *|
|* Motor Port 3 leftMotor VEX 3-wire module Left side motor *|
\*-----------------------------------------------------------------------------------------------*/
// This program makes a sharp turn using the encoders for reproducable accuracy.
const int UMMAL = 32;
void stop_motors(int sop_time){
	motor[leftMotor]=0;
	motor[rightMotor]=0;
	wait1Msec(sop_time);
}
void EncoderReset(){
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
}
void drive(int dist){
EncoderReset();

while(dist > abs(SensorValue[rightEncoder]))
  {
    if(abs(SensorValue[rightEncoder]) == abs(SensorValue[leftEncoder])) // If rightEncoder has counted the same amount as leftEncoder:
		{
			motor[rightMotor] = 60;		    // Right Motor is run at power level 60
			motor[leftMotor]  = 80;
		}
		else if(abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))	// If rightEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[rightMotor] = 60;		    // Right Motor is run at power level 60
			motor[leftMotor]  = 80;		    // Left Motor is run at power level 80
		}
		else	// Only runs if leftEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[rightMotor] = 80;		    // Right Motor is run at power level 80
			motor[leftMotor]  = 60;		    // Left Motor is run at power level 60
		}
  }
};
void Turn(int deg,bool b_f){
	EncoderReset();
	if(b_f == 1){
	while(abs(SensorValue[leftEncoder]) < (deg/UMMAL)*340/4)
{
		motor[rightMotor] = 80;
		motor[leftMotor]  = -80;
}
}
else if(b_f == 0){
		while(abs(SensorValue[rightEncoder]) < (deg/UMMAL)*340/4)
{
		motor[rightMotor] = -80;
		motor[leftMotor]  = 80;
}
}
EncoderReset();
}



task main()
{

 	bool turnarray[14] = {0,1,1,0,0,1,1,0,0,1,1,0,1,1};
  for(int i = 1;i <= 14 ;i++)
  	{
  		EncoderReset();
  		stop_motors(1000);
  		drive(250);
  		Turn(90,turnarray[i]);

  }
}
