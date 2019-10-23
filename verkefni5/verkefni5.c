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
|*                                 						Verkefni 5 					                                *|
|*  The robot follows a line using the 3 linefollowers and uses a task Killswitch as a emergency
    button

	//hvit 1.490avg on the three
	//svart 2737
	//2113.5
\*------------------------------------------------------------------------------------------------*/
task main()
{
StartTask(Killswitch);
  wait1Msec(2000);          // The program waits for 2000 milliseconds before continuing.

  int threshold = 2113.5;      /* found by taking a reading on both DARK and LIGHT    */
                            /* surfaces, adding them together, then dividing by 2. */
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

    // RIGHT sensor sees dark:
    if(SensorValue(rightLineFollower) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = 63;
      motor[rightMotor] = 0;
    }
    // CENTER sensor sees dark:
    if(SensorValue(centerLineFollower) > threshold)
    {
      // go straight
      motor[leftMotor]  = 63;
      motor[rightMotor] = 63;
    }
    // LEFT sensor sees dark:
    if(SensorValue(leftLineFollower) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 63;
    }
    else{
    	motor[leftMotor]  = 0;
      motor[rightMotor] = 63;
    }
    if(SensorValue(leftLineFollower) > threshold && SensorValue(rightLineFollower) > threshold && SensorValue(centerLineFollower) > threshold )
    {
      // counter-steer left:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 0;
    }
  }
StopTask(Killswitch);
}
