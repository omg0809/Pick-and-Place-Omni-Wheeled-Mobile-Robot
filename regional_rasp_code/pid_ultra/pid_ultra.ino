#include <util/atomic.h> // For the ATOMIC_BLOCK macro

/////// E C H O ///////
#define echoF 51
#define echoR 10
#define echoL 12
#define echoB 14
int echo[4] = {51,10,12,14};

/////// T R I G ///////
#define trigF 50
#define trigR 11
#define trigL 13
#define trigB 15
int trig[4] = {50,11,13,15};

////// Ultrasonic Variables ////////
long duration;
int distanceF, distanceL, distanceR, distanceB;
int dist;

/////// C H A ////////
#define enc_A1 2
#define enc_A2 3
#define enc_A3 18
#define enc_A4 19
int encA[4] = {2,3,18,19};

/////// C H B ////////
#define enc_B1 31
#define enc_B2 33
#define enc_B3 35
#define enc_B4 37
int encB[4] = {31,33,35,37};

/////// P W M ////////
#define m1_pwm 9
#define m2_pwm 8
#define m3_pwm 7
#define m4_pwm 6
int m_pwm[4] = {9,8,7,6};

/////// D I R ////////
#define m1 30
#define m2 36
#define m3 34
#define m4 32
int m[4] = {30,32,34,36};

volatile int posi[4] = {0,0,0,0};
long prevT[4] = {0,0,0,0};
float eprev[4] = {0,0,0,0};
float eintegral[4] = {0,0,0,0};

int pos,pwr;
int dir;
float ratio;

// PID constants
float kp[4] = {10,10,10,10};
float kd[4] = {1,1,1,1};
float ki[4] = {0,0,0,0};

int tar = 500;
int d = 1; 
int target[4] = {tar,-tar,-tar,tar};        //forward
//int target[4] = {-tar,tar,tar,-tar};        //backward
//int target[4] = {tar,tar,-tar,-tar};        //right
//int target[4] = {-tar,-tar,tar,tar};        //left
//int target = 250*sin(prevT/1e6);

char val;  
int Mspeed = 150;
int Mstop = 0;
int Mturn = 100;
int reached = 0;      // To check if the robot has reached the desired speed.

//////////////////////// S E T U P ///////////////////////////

void setup() {
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(encA[0]),readEncoder_m1,RISING);
  attachInterrupt(digitalPinToInterrupt(encA[1]),readEncoder_m2,RISING);
  attachInterrupt(digitalPinToInterrupt(encA[2]),readEncoder_m3,RISING);
  attachInterrupt(digitalPinToInterrupt(encA[3]),readEncoder_m4,RISING);
  
  for (int k = 8 ; k <= 14 ; k=k+2) {                  
   pinMode(k, INPUT);
  }

  for (int k = 9 ; k <= 15 ; k=k+2) {                  
   pinMode(k, OUTPUT);
  }
  
  for (int k = 18 ; k <= 28 ; k++) {                  
   pinMode(k, INPUT);
  }

  for (int k = 4 ; k <= 7 ; k++) {                  
   pinMode(k, OUTPUT);
  }

  for (int k = 30 ; k <= 38 ; k=k+2) {                  
   pinMode(k, OUTPUT);
  }
}

////////////////////// L O O P ///////////////////////////

void loop() {
    pid(0);
    pid(1);
    pid(2);
    pid(3);
  // put your main code here, to run repeatedly:
  /*if (reached != 1)  {
    pid(0);
    pid(1);
    pid(2);
    pid(3);
  }
  else  {
    stopAll();
    distanceF = ReadUltrasonic(trigF,echoF);
    if (distanceF > 18) {
      while (distanceF > 18)  {
        forward();
      }
    }
    else if (distanceF < 13)  {
      while (distanceF < 13)  {
        backward();
      }
    }
    else{
      stopAll();
    }
    
  }*/
  
}

////////////////////// P I D ///////////////////////////

void pid(int i)  {
  //int i=1;
  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT[i]))/( 1.0e6 );
  prevT[i] = currT;

  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi[i];
  }
  
  // error
  int e = pos - target[i];

  // derivative
  float dedt = (e-eprev[i])/(deltaT);

  // integral
  eintegral[i] = eintegral[i] + e*deltaT;

  // control signal
  float u = kp[i]*e + kd[i]*dedt + ki[i]*eintegral[i];

  // motor power
  float pwr = fabs(u);
  
  ratio = abs(float(pos))/abs(float(tar));
  

  if( pwr > 255 ){
    pwr = 255;
  }
  if( pwr < 50 ){
    pwr = 0;
  }

  /*
  if (ratio <= 0.3 || ratio >=  0.7 )  {
    pwr = (pwr/255)*100;
  }*/
  /*else if (ratio > 0.3 && ratio < 0.7 )  {
    pwr = (pwr/255)*255;
  }*/

  
  // motor direction
  int dir = 1;
  if(u<0){
    dir = -1;
  }

  if (i == 1 || i == 2) {dir = -dir;}
  
  // signal the motor
  setMotor(i,dir,pwr);


  // store previous error
  eprev[i] = e;

  /*
  Serial.print(" ");
  Serial.print(tar);
  Serial.print(" ");
  Serial.print(pos);
  Serial.print(" ");
  Serial.print(pwr);
  Serial.println();*/
  
}

////////////////// Set Motors ///////////////////////
void setMotor(int j, int dir, int pwmVal){
  //j=1;
  int M, pwm;
  if (j == 0) {M = m[0]; pwm = m_pwm[0];}
  if (j == 1) {M = m[1]; pwm = m_pwm[1];}
  if (j == 2) {M = m[2]; pwm = m_pwm[2];}
  if (j == 3) {M = m[3]; pwm = m_pwm[3];}
  
  if(dir == 1){
    digitalWrite(M, HIGH);
    analogWrite(pwm, pwmVal);
    reached = 0;
  }
  else if(dir == -1){
    digitalWrite(M, LOW);
    analogWrite(pwm, pwmVal);
    reached = 0;
  }
  else{
    analogWrite(pwm, 0);
    reached = 1;
  }  
}

////////////// E N C O D E R ///////////////
void readEncoder_m1(){
  
  int b = digitalRead(encB[0]);
  if(b > 0){
    posi[0]++;
  }
  else{
    posi[0]--;
  }
}

void readEncoder_m2(){
  
  int b = digitalRead(encB[1]);
  if(b > 0){
    posi[1]++;
  }
  else{
    posi[1]--;
  }
}

void readEncoder_m3(){
  
  int b = digitalRead(encB[2]);
  if(b > 0){
    posi[2]++;
  }
  else{
    posi[2]--;
  }
}

void readEncoder_m4(){
  
  int b = digitalRead(encB[3]);
  if(b > 0){
    posi[3]++;
  }
  else{
    posi[3]--;
  }
}

/////////////// Read Ultrasonic ////////////////

int ReadUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);    
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist = duration * 0.034 / 2;
  delay(100);

  return dist;
}

/////////////////// Motor Functions /////////////////

void forward(){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, HIGH);
  analogWrite(m1_pwm, Mspeed);
  analogWrite(m2_pwm, Mspeed);
  analogWrite(m3_pwm, Mspeed);
  analogWrite(m4_pwm, Mspeed);
}

void backward(){
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  analogWrite(m1_pwm, Mspeed);
  analogWrite(m2_pwm, Mspeed);
  analogWrite(m3_pwm, Mspeed);
  analogWrite(m4_pwm, Mspeed);
}

void stopAll(){
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
  //digitalWrite(gu, LOW);
  //digitalWrite(gd, LOW);
  analogWrite(m1_pwm, Mstop);
  analogWrite(m2_pwm, Mstop);
  analogWrite(m3_pwm, Mstop);
  analogWrite(m4_pwm, Mstop);
}