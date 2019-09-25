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

// detta program keyrir afram og tilbaka med encoders til ad keyra beint Ummal hjol er 10.4 * PI = 32.67 eda 33
const int UMMAL = 33;
const int LENGTH = 500;
void EncoderReset()
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;


};
void drive(int dist,bool b_f){

int dir = (b_f)? (1):(-1);
EncoderReset();

while(dist > abs(SensorValue[rightEncoder]))
  {

    if(abs(SensorValue[rightEncoder]) == abs(SensorValue[leftEncoder]))
		{
			motor[rightMotor] = 60*dir;		    // Right Motor is run at power level 60
			motor[leftMotor]  = 80*dir;
		}
		else if(abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))	// If rightEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[rightMotor] = 60*dir;		    // Right Motor is run at power level 60
			motor[leftMotor]  = 80*dir;		    // Left Motor is run at power level 80
		}
		else	// Only runs if leftEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[rightMotor] = 80*dir;		    // Right Motor is run at power level 80
			motor[leftMotor]  = 60*dir;		    // Left Motor is run at power level 60
		}

  }
};
task main()
{

  for(int counter =1;counter<=5;counter++){
 drive(LENGTH*counter,true);
 drive(LENGTH*counter,false);
}
}
