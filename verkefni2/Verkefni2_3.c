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
// detta program fer i gegnum maze fyrir verkefni 2.3 notar void turn til ad beygja og drive til ad keyra afram allt med encoderum
\*-----------------------------------------------------------------------------------------------*/

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
			motor[rightMotor] = 80;		    // Right Motor is run at power level 60
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
	while(abs(SensorValue[leftEncoder]) < (deg/UMMAL)*335/4)
{
		motor[rightMotor] = 80;
		motor[leftMotor]  = -80;
}
}
else if(b_f == 0){
		while(abs(SensorValue[rightEncoder]) < (deg/UMMAL)*335/4)
{
		motor[rightMotor] = -80;
		motor[leftMotor]  = 80;
}
}
EncoderReset();
}



task main()
{

 	bool turnarray[14] = {0,1,1,0,0,1,0,0,1,0,0,1,1,0};
  for(int i = 0;i <= 14 ;i++)
  	{
  		EncoderReset();
  		stop_motors(1000);
  		drive(250);
  		Turn(90,turnarray[i]);

  }
}
