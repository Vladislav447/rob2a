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

 /*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Moving Forward7
This program instructs your robot to move forward at full power for three seconds.
There is a two second pause at the beginning of the program.

Robot Model(s): Squarebot

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        rightMotor          VEX Motor             Right side motor
Motor Port 3        leftMotor           VEX Motor             Left side motor

*To run this sample program on Swervebot, be sure to Reverse Motor Port 3 in the Motors and Sensors
 Setup, and to make sure that Motor Port 2 is NOT Reversed.
----------------------------------------------------------------------------------------------------*/


//keyrir fram og til baka 5 skipti
const int BASETIME =1000;
int power = 127;

void Drive_Forward(int counter){
	motor[rightMotor] = power;
	motor[leftMotor]  = power;
	wait1Msec(counter*BASETIME);
}
void Drive_Backwards(int counter){
	motor[rightMotor] = -power;
	motor[leftMotor]  = -power;
	wait1Msec(counter*BASETIME);
}
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
				for(int counter = 1; counter <= 5;counter++){
				 Drive_Forward(counter);
				 Drive_Backwards(counter);
				}
}												        // Program ends, and the robot stops
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
