#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA_L 18
#define ENCB_L 19 
#define ENCA_R 2 
#define ENCB_R 3
#define ENCA_B 20
#define ENCB_B 21 

#define MR 30                                                                                                                                             
#define ML 32
#define MB 34

#define MR_en 9
#define ML_en 8
#define MB_en 7

//////////////// R ////////////////////
volatile int posi_R = 0; 
long prevT_R = 0;
float eprev_R = 0;
float eintegral_R = 0;

int pos_R,pwr_R;
int dir_R;

// set target position
int target_R = -500;
//int target = 250*sin(prevT/1e6);

// PID constants
float kp_R = 8;
float kd_R = 0.07;
float ki_R = 0;

//////////////// L ////////////////////
volatile int posi_L = 0; 
long prevT_L = 0;
float eprev_L = 0;
float eintegral_L = 0;

int pos_L,pwr_L;
int dir_L;

// set target position
int target_L = 500;
//int target = 250*sin(prevT/1e6);

// PID constants
float kp_L = 8;
float kd_L = 0.07;
float ki_L = 0;

//////////////// B ////////////////////
volatile int posi_B = 0; 
long prevT_B = 0;
float eprev_B = 0;
float eintegral_B = 0;

int pos_B,pwr_B;
int dir_B;

// set target position
int target_B = 100;
//int target = 250*sin(prevT/1e6);

// PID constants
float kp_B = 8;
float kd_B = 0.07;
float ki_B = 0;
///////////////////////////////////////

char val;  
int Mspeed = 255;
int Mstop = 0;
int Mturn = 100;

void setup() {
  Serial.begin(9600);
  
  pinMode(ENCA_R,INPUT);
  pinMode(ENCB_R,INPUT);
  pinMode(ENCA_L,INPUT);
  pinMode(ENCB_L,INPUT);
  pinMode(ENCA_B,INPUT);
  pinMode(ENCB_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA_R),readEncoder_R,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_L),readEncoder_L,RISING);
  //attachInterrupt(digitalPinToInterrupt(ENCA_B),readEncoder_B,RISING);

  for (int i = 5 ; i <= 7 ; i++) {                  
   pinMode(i, OUTPUT);
  }
  

  for (int i = 30 ; i <= 34 ; i=i+2) {                  
   pinMode(i, OUTPUT);
  }

  digitalWrite(MB, HIGH);
  analogWrite(MB_en, 0);
  
  Serial.println("target pos");
}

void loop() {
  
  PID_R();
  PID_L();
  //PID_B();
  
}

////////////////////// PID L ///////////////////////////

void PID_L()  {
  
  // time difference
  long currT_L = micros();
  float deltaT_L = ((float) (currT_L - prevT_L))/( 1.0e6 );
  prevT_L = currT_L;

  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos_L = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos_L = posi_L;
  }
  
  // error
  int e_L = pos_L - target_L;

  // derivative
  float dedt_L = (e_L-eprev_L)/(deltaT_L);

  // integral
  eintegral_L = eintegral_L + e_L*deltaT_L;

  // control signal
  float u_L = kp_L*e_L + kd_L*dedt_L + ki_L*eintegral_L;

  // motor power
  float pwr_L = fabs(u_L);
  if( pwr_L > 255 ){
    pwr_L = 255;
  }
  if( pwr_L < 80 ){
    pwr_L = 0;
  }

  // motor direction
  int dir_L = 1;
  if(u_L<0){
    dir_L = -1;
  }

  // signal the motor
  setMotor_L(dir_L,pwr_L);


  // store previous error
  eprev_L = e_L;

  Serial.print(" ");
  Serial.print(target_L);
  Serial.print(" ");
  Serial.print(pos_L);
  Serial.print(" ");
  Serial.print(pwr_L);
  Serial.println();
  
}

/////////////////// PID R ///////////////////////////

void PID_R()  {
  
  // time difference
  long currT_R = micros();
  float deltaT_R = ((float) (currT_R - prevT_R))/( 1.0e6 );
  prevT_R = currT_R;

  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos_R = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos_R = posi_R;
  }
  
  // error
  int e_R = pos_R - target_R;

  // derivative
  float dedt_R = (e_R-eprev_R)/(deltaT_R);

  // integral
  eintegral_R = eintegral_R + e_R*deltaT_R;

  // control signal
  float u_R = kp_R*e_R + kd_R*dedt_R + ki_R*eintegral_R;

  // motor power
  float pwr_R = fabs(u_R);
  if( pwr_R > 255 ){
    pwr_R = 255;
  }
  if( pwr_R < 80 ){
    pwr_R = 0;
  }

  // motor direction
  int dir_R = 1;
  if(u_R<0){
    dir_R = -1;
  }

  // signal the motor
  setMotor_R(dir_R,pwr_R);


  // store previous error
  eprev_R = e_R;
/*
  Serial.print(" ");
  Serial.print(target_R);
  Serial.print(" ");
  Serial.print(pos_R);
  Serial.print(" ");
  Serial.print(pwr_R);
  Serial.println();
  */
}

////////////////// Set Motors ///////////////////////
void setMotor_R(int dir, int pwmVal){
  
  if(dir == 1){
    digitalWrite(MR, HIGH);
    analogWrite(MR_en, pwmVal);
  }
  else if(dir == -1){
    digitalWrite(MR, LOW);
    analogWrite(MR_en, pwmVal);
  }
  else{
    analogWrite(MR_en, 0);
  }  
}

void setMotor_L(int dir, int pwmVal){
  
  if(dir == 1){
    digitalWrite(ML, HIGH);
    analogWrite(ML_en, pwmVal);
  }
  else if(dir == -1){
    digitalWrite(ML, LOW);
    analogWrite(ML_en, pwmVal);
  }
  else{
    analogWrite(ML_en, 0);
  }  
}


///////////////// encoder //////////////////////////
void readEncoder_R(){
  
  int b = digitalRead(ENCB_R);
  if(b > 0){
    posi_R++;
  }
  else{
    posi_R--;
  }
}

void readEncoder_L(){
  
  int b = digitalRead(ENCB_L);
  if(b > 0){
    posi_L++;
  }
  else{
    posi_L--;
  }
}