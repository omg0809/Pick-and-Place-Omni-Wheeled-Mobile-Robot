#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA 18 
#define ENCB 2
#define ENCC 20

#define MR 30                                                                                                                                             
#define ML 32
#define MB 34

#define MR_en 9
#define ML_en 8
#define MB_en 7

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;
int count = 0;

char val;  
int Mspeed = 255;
int Mstop = 0;
int Mturn = 100;

void setup() {
  Serial.begin(9600);
  
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(ENCC,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoderA,CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCB),readEncoderB,CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCC),readEncoderC,CHANGE);

  pinMode(MR, OUTPUT);
  pinMode(ML, OUTPUT);
  pinMode(MB, OUTPUT);

  pinMode(MR_en, OUTPUT);
  pinMode(ML_en, OUTPUT);
  pinMode(MB_en, OUTPUT);
  
  Serial.println("target pos");
}

void loop() {

  // set target position
  int target = 100;
  //int target = 250*sin(prevT/1e6);
  

  // PID constants
  float kp = 8;
  float kd = 0.07;
  float ki = 0;

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;

  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }
  
  // error
  int e = pos - target;

  // derivative
  float dedt = (e-eprev)/(deltaT);

  // integral
  eintegral = eintegral + e*deltaT;

  // control signal
  float u = kp*e + kd*dedt + ki*eintegral;

  // motor power
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }

  // motor direction
  int dir = 1;
  if(u<0){
    dir = -1;
  }

  // signal the motor
  setMotor(dir,pwr);


  // store previous error
  eprev = e;

  Serial.print(" ");
  Serial.print(target);
  Serial.print(" ");
  Serial.print(pos);
  Serial.print(" ");
  Serial.print(pwr);
  Serial.println();
}

void setMotor(int dir, int pwmVal){
  
  if(dir == 1){
    digitalWrite(MR, HIGH);
    digitalWrite(ML, LOW);
    digitalWrite(MB, HIGH);
    analogWrite(MR_en, pwmVal);
    analogWrite(ML_en, pwmVal);
    analogWrite(MB_en, 0);
  }
  else if(dir == -1){
    digitalWrite(MR, LOW);
    digitalWrite(ML, HIGH);
    digitalWrite(MB, LOW);
    analogWrite(MR_en, pwmVal);
    analogWrite(ML_en, pwmVal);
    analogWrite(MB_en, 0);
  }
  else{
    analogWrite(MR_en, 0);
    analogWrite(ML_en, 0);
    analogWrite(MB_en, 0);
  }  
}

void readEncoderA(){
  
  int a = digitalRead(ENCA);
  if(a > 0){
    posi++;
  }
  else{
    posi--;
  }
}

void readEncoderB(){
  
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}

void readEncoderC(){
  
  int c = digitalRead(ENCC);
  if(c > 0){
    posi++;
  }
  else{
    posi--;
  }
}