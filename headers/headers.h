
const int UMMAL = 32;
const int BASEDIST =500;
void DriveEncoder(int dist);
void EncoderTurn(int deg,bool b_f);
void Stop_Motors(int sop_time);
void EncoderReset();
void Light_Sensor();
void Turn();
task Killswitch();
task Battery();
task Controller();
