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
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           Armmotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           Clawmotor,     tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**************************\
|*  ROBOTC Virtual World  *|
|*  Turning with Encoders *|
\**************************/

// This program makes a sharp turn using the encoders for reproducable accuracy.
const int BASETURNROTATION = 320;
int BASEROTATION = 500;
int power = 127;
void Drive_Forward(){
	motor[rightMotor] = power;
	motor[leftMotor]  = power;

}
void Turn_Left(){
		motor[rightMotor] = power;
		motor[leftMotor]  = -power;
}
void Turn_Right(){
		motor[rightMotor] = -power;
		motor[leftMotor]  = power;
}
void Reset(){
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
}
task main()
{
  Reset();

  while(SensorValue[rightEncoder] < BASEROTATION)  // while the right encoder value is less than 100:
  {
     Drive_Forward();

  }
   Reset();
   while(SensorValue[leftEncoder] > -BASETURNROTATION)  // while the right encoder value is less than 100:
  {
     Turn_Left();
  }
  Reset();
  while(SensorValue[rightEncoder] < BASEROTATION)  // while the right encoder value is less than 100:
  {
     Drive_Forward();
  }
   Reset();
  while(SensorValue[rightEncoder] > -BASETURNROTATION)  // while the right encoder value is less than 100:
  {
     Turn_Right();
  }
  Reset();
  while(SensorValue[rightEncoder] < BASEROTATION)  // while the right encoder value is less than 100:
  {
     Drive_Forward();
  }
  Reset();
  while(SensorValue[rightEncoder] > -BASETURNROTATION)  // while the right encoder value is less than 100:
  {
     Turn_Right();
  }
  Reset();
  while(SensorValue[rightEncoder] < BASEROTATION)  // while the right encoder value is less than 100:
  {
     Drive_Forward();

  }
}