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
#include "../includes/headers/headers.h"
#include "../includes/functions/motor_encoder.inc"
/*------------------------------------------------------------------------------------------------*\
|*                                 						Verkefni 4 					                                *|
|*                                 					               				                                *|
|* 						verkefnid er um ad nota sonar og light sonar til ad keyra endalaust an dess ad rekast
													  a hluti og tad a ad nota killswitch lika
													  ljost value = 130 dokt value = 481 totalvalue/3 299 ~ 300
\*------------------------------------------------------------------------------------------------*/
task main(){
	StartTask(killswitch);
	StartTask(battery);
wait1Msec(2000);						// Robot waits for 2000 milliseconds before executing program
while(1==1)
	{
	while(SensorValue(sonarSensor) > 40  || SensorValue(sonarSensor) == -1)		// Loop while robot's Ultrasonic sensor is further than 20 inches away from an object
	{                                                                         // || (or) it is '-1'.  (-1 is the value returned when nothing is in it's visable range)
		motor[rightMotor] = 63;			// Motor on port2 is run at half (63) power forward
		motor[leftMotor]  = 63;			// Motor on port3 is run at half (63) power forward
		Light_sensor();//if light_sensor > 300 stoppar hann ef ekki gerir hann ekkert
	}
	stop_motors(1000);//stoppar í 1 secondu
	Turn();//notar rand%2 til ad beygja
	Light_sensor();//if light_sensor > 300 stoppar hann ef ekki gerir hann ekkert
}
StopTask(battery);
StopTask(killswitch);
}
