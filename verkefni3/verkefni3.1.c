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
|* - Moving using controller - *|
verkefni 3.1
Forriti� fjarst�ringu �annig a� annar sn��ur e�a b��ir virka til a� f�ra r�bot fram og aftur sem og sn�a.
Forriti� einnig tvo hnappa fyrir arm �.e lyfta ,s�ga og opna / loka kl�.
\*-----------------------------------------------------------------------------------------------*/

#include "../includes/headers/headers.h"
#include "../includes/functions/motor_encoder.inc"
task main()
{
while(1 == 1){
	 motor[leftMotor]  = vexRT[Ch3]/ 2;
   motor[rightMotor] = vexRT[Ch2]/ 2;
	if(vexRT[Btn6U] == 1)
	{
		motor[Clawmotor]= 40;
	}
  else if
  	(vexRT[Btn6D] == 1)
	{
	motor[Clawmotor]= -40;
	}

 	if(vexRT[Btn5U] == 1)
	{
		motor[Armmotor] = 40;
	}
  else if
  	(vexRT[Btn5D] == 1)
	{
	  motor[Armmotor] = -40;
	}
	else{
   motor[Clawmotor] = 0;
   motor[Armmotor] = 0;
 }
}

}
