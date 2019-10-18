void Light_Sensor()
{
	while (SensorValue(lightsensor) > 300)//ef hann fer yfir 300 setur motors ad 0
	{
			motor[rightMotor] = 0;
		  motor[leftMotor]  = 0;
	}
}
void Turn(){
	EncoderReset();
	int rando = rand()%2;
	if(rando == 1){
	while(abs(SensorValue[leftEncoder]) < (90/UMMAL)*335/4)
{
		motor[rightMotor] = 63;
		motor[leftMotor]  = -63;
}
}
else if(rando == 2){
		while(abs(SensorValue[rightEncoder]) < (90/UMMAL)*335/4)
{
		motor[rightMotor] = -63;
		motor[leftMotor]  = 63;
}
}
}
task Killswitch()//killswitch task
{
	while (true)
	{
		if (vexRT[Btn7U] !=0)
		{
			StopAllTasks();
		}
		else if(SensorValue(bumper) == 1)
	{
			StopAllTasks();
	}
		wait1Msec(20);
	}
	return;
}
task Controller()//controller task
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

	return;
}
task Battery()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}
void Stop_Motors(int sop_time){
	motor[leftMotor]=0;
	motor[rightMotor]=0;
	wait1Msec(sop_time);
}
void EncoderReset(){
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
}
void DriveEncoder(int dist){
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
void EncoderTurn(int deg,bool b_f){
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
