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
		robot followes line and picks up glass
		while following line(if it loses the line it reverses back.)
		and then returns it to a basket also uses lightsensor	to stop if it gets dark
\*------------------------------------------------------------------------------------------------*/
#include "../includes/headers/headers.h"
#include "../includes/functions/motor_encoder.inc"
/*bool wasright = true;
void findline(){
motor[rightMotor] = -30;
motor[leftMotor] = -30;
wait1Msec(1000);
motor[rightMotor] = 30;
motor[leftMotor] = -30;
}*/
void turnaround(){//turns around 180 degrees
	while(abs(SensorValue[leftEncoder]) < (180/UMMAL)*335/4)
{
		motor[rightMotor] = -80;
		motor[leftMotor]  = 80;
}
}

void claw(int a){//closes or opens claw depending if its 1 or -1
	motor[Clawmotor]=a*40;
	wait1Msec(1000);
	motor[Clawmotor]=0;
}
void liftarm(){//lifts arm
		motor[Armmotor] = -60;
		wait1Msec(250);
		motor[Armmotor] = 0;
}
void lowerarm(){
	motor[Armmotor] = 60;//lowers arm
	wait1Msec(250);
	motor[Armmotor] = 0;
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
		Light_Sensor();// fetches the light_sensor function
    // CENTER sensor sees dark:
    if(SensorValue(centerLineFollower) > threshold)
    {
      // go straight
    	motor[leftMotor]  = 30;
      motor[rightMotor] = 30;
    }
     // RIGHT sensor sees dark:
    if(SensorValue(rightLineFollower) > threshold)
    {
    	// wasright = true;
      // counter-steer right:
      motor[leftMotor]  = 40;
      motor[rightMotor] = 0;
    }
    // LEFT sensor sees dark:
    if(SensorValue(leftLineFollower) > threshold)
    {
    	// wasright = false;
    	// counter-steer left:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 40;
    }
   motor[leftMotor] = 0;
   motor[rightMotor] = 0;
 }
};
bool takeglass = true;
task findglass(){
	while(true){
	if(SensorValue(sonarSensor) > 20  || SensorValue(sonarSensor) == -1 && findglass == true)//if sonar value is within 25cm it starts the following things
	{
					StopTask(followline);
					Stop_Motors(1000);
					claw(1);
					Stop_Motors(1000);
					liftarm();
					Stop_Motors(1000);
					claw(-1);
					Stop_Motors(1000);
					turnaround();
					Stop_Motors(1000);
					takeglass = false;
					StartTask(followline);
	}
	if(SensorValue(centerLineFollower)< threshold && SensorValue(rightLineFollower) < threshold && SensorValue(leftLineFollower)< threshold && findglass == false){
		claw(1);
		StopAllTasks();
	}
	}
}
task main(){
StartTask(Killswitch);
StartTask(followline);
StartTask(findglass);
}
