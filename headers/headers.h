
const int UMMAL = 32;
const int BASEDIST =500;
void driveencoder(int dist);
void encoderTurn(int deg,bool b_f);
void stop_motors(int sop_time);
void EncoderReset();
void Light_sensor();
void Turn();
task killswitch();
task battery();
