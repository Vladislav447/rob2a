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

/*------------------------------------------------------------------------------------------------*\
|*                                 						Verkefni 6 					                                *|
		robot goes through maze picking up glasses and then returns them to a basket also uses liglightsensor
		to stop if it gets dark
\*------------------------------------------------------------------------------------------------*/
#include "../includes/headers/headers.h"
#include "../includes/functions/motor_encoder.inc"
bool right;
void findline(){
	if(right == true){
			motor[leftMotor]  = -halfpower;
      motor[rightMotor] = 0;
      if(SensorValue(leftLineFollower) > threshold){
    }
    if(SensorValue(centerLineFollower) > threshold){
    }
    if(SensorValue(rightLineFollower) > threshold){
    }
	}
	if(right == false){
		motor[leftMotor]  = 0;
    motor[rightMotor] = -halfpower;
    if(SensorValue(leftLineFollower) > threshold){
    }
    if(SensorValue(centerLineFollower) > threshold){
    }
    if(SensorValue(rightLineFollower) > threshold){

    }

	}

}
task followline(){

	while(true)
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+
    displayLCDCenteredString(0, "LEFT  CNTR  RGHT");        //  Display   |
    displayLCDPos(1,0);                                     //  Sensor    |
    displayNextLCDNumber(SensorValue(leftLineFollower));    //  Readings  |
    displayLCDPos(1,6);                                     //  to LCD.   |
    displayNextLCDNumber(SensorValue(centerLineFollower));  //            |
    displayLCDPos(1,12);                                    //  L  C  R   |
    displayNextLCDNumber(SensorValue(rightLineFollower));   //  x  x  x   |
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+
		Light_Sensor();
		driveforward();
    // CENTER sensor sees dark:
    if(SensorValue(centerLineFollower) > threshold)
    {
      // go straight
			Light_Sensor();
			EncoderReset();
    }
     // RIGHT sensor sees dark:
   if(SensorValue(rightLineFollower) > threshold){
     right=true;
     Light_Sensor();
     EncoderReset();
    }
    if(SensorValue(leftLineFollower) > threshold)
    {
    	right=false;
    	motor[leftMotor]  = halfpower;
      motor[rightMotor] = 0;
      Light_Sensor();
    }
 		if(SensorValue(centerLineFollower)> threshold && SensorValue(rightLineFollower) > threshold && SensorValue(leftLineFollower)> threshold)
  {
  	Stop_Motors(2000);
  	findline();
  }
 }

};

void turnaround(){
	while(abs(SensorValue[leftEncoder]) < (180/UMMAL)*335/4)
{
		motor[rightMotor] = 0;
		motor[leftMotor]  = -80;
}
}
void Claw(bool open_close){
	int claw = (open_close)? (1):(-1);
	motor[Clawmotor]=claw*40;

}
void lift(bool lift){
	int arm = (lift)? (1):(-1);
	motor[Armmotor]=arm*40;
}
bool array[12] = {
	{0,1,0,1,0,0,1,0,0,1,0,1,1,0,1,0}};
int counter = 0;
task main()
{
	StartTask(Killswitch);
	StartTask(followline);
	for(int j = 0; j <= 13; j++){
	DriveEncoder(BASEDIST);
	Stop_Motors(1000);
	EncoderTurn(90,array[j]);
	Stop_Motors(1000);
	counter++;
	DriveEncoder(BASEDIST*5/j);
	Stop_Motors(1000);
	EncoderTurn(90,array[j]);
	Stop_Motors(1000);
	counter++;
	DriveEncoder(BASEDIST);
	Stop_Motors(1000);
	lift(false);
	Stop_Motors(1000);
	Claw(true);
	Stop_Motors(1000);
	lift(true);
	Stop_Motors(1000);
	turnaround();
	Stop_Motors(1000);
	DriveEncoder(BASEDIST);
	Stop_Motors(1000);
	EncoderTurn(90,array[j]);
	Stop_Motors(1000);
	counter++;
	DriveEncoder(BASEDIST*5/j);
	Stop_Motors(1000);
	EncoderTurn(90,array[j]);
	Stop_Motors(1000);
	counter++;
	DriveEncoder(BASEDIST);
	Stop_Motors(1000);
	lift(false);
	Stop_Motors(1000);
	Claw(false);
	Stop_Motors(1000);
	lift(true);
	Stop_Motors(1000);
	turnaround();
  Stop_Motors(1000);
  }
}
