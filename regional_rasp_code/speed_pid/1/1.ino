#include <util/atomic.h>

// Pins
#define ENCA_1 2
#define ENCB_1 31
#define PWM_1 9
#define IN1 30

#define ENCA_2 3
#define ENCB_2 33
#define PWM_2 8
#define IN2 32

#define ENCA_3 18
#define ENCB_3 35
#define PWM_3 7
#define IN3 34

#define ENCA_4 19
#define ENCB_4 37
#define PWM_4 6
#define IN4 36

// globals
long prevT = 0;
int posPrev = 0;
// Use the "volatile" directive for variables
// used in an interrupt
volatile int pos_i = 0;
volatile float velocity_i = 0;
volatile long prevT_i = 0;

float v1Filt = 0;
float v1Prev = 0;
float v2Filt = 0;
float v2Prev = 0;

float eintegral = 0;

void setup() {
  Serial.begin(115200);

  pinMode(ENCA_1,INPUT);
  pinMode(ENCB_1,INPUT);
  pinMode(PWM_1,OUTPUT);
  pinMode(IN1,OUTPUT);

  pinMode(ENCA_2,INPUT);
  pinMode(ENCB_2,INPUT);
  pinMode(PWM_2,OUTPUT);
  pinMode(IN2,OUTPUT);

  pinMode(ENCA_3,INPUT);
  pinMode(ENCB_3,INPUT);
  pinMode(PWM_3,OUTPUT);
  pinMode(IN3,OUTPUT);

  pinMode(ENCA_4,INPUT);
  pinMode(ENCB_4,INPUT);
  pinMode(PWM_4,OUTPUT);
  pinMode(IN4,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA_1),readEncoder_1,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_2),readEncoder_2,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_3),readEncoder_3,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_4),readEncoder_4,RISING);
}

void loop() {

  // read the position in an atomic block
  // to avoid potential misreads
  int pos = 0;
  float velocity2 = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    pos = pos_i;
    velocity2 = velocity_i;
  }

  // Compute velocity with method 1
  long currT = micros();
  float deltaT = ((float) (currT-prevT))/1.0e6;
  float velocity1 = (pos - posPrev)/deltaT;
  posPrev = pos;
  prevT = currT;

  // Convert count/s to RPM
  float v1 = velocity1/600.0*60.0;
  float v2 = velocity2/600.0*60.0;

  // Low-pass filter (25 Hz cutoff)
  v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  v1Prev = v1;
  v2Filt = 0.854*v2Filt + 0.0728*v2 + 0.0728*v2Prev;
  v2Prev = v2;

  // Set a target
  float vt = 100*(sin(currT/1e6)>0);

  // Compute the control signal u
  float kp = 1;
  float ki = 1;
  float e = vt-v1Filt;
  eintegral = eintegral + e*deltaT;
  
  float u = kp*e + ki*eintegral;

  // Set the motor speed and direction
  int dir = 1;
  if (u<0){
    dir = -1;
  }
  int pwr = (int) fabs(u);
  if(pwr > 255){
    pwr = 255;
  }
  setMotor1(-1,pwr,PWM_1,IN1);
  setMotor2(1,pwr,PWM_2,IN2);
  setMotor3(1,pwr,PWM_3,IN3);
  setMotor4(-1,pwr,PWM_4,IN4);
  

  Serial.print(vt);
  Serial.print(" ");
  Serial.print(v1Filt);
  Serial.println();
  delay(1);
}

void setMotor1(int dir, int pwmVal, int pwm, int in1){
  analogWrite(pwm,pwmVal); // Motor speed
  if(dir == 1){ 
    // Turn one way
    digitalWrite(in1,HIGH);
  }
  else if(dir == -1){
    // Turn the other way
    digitalWrite(in1,LOW);
  }
  else{
    // Or dont turn
    digitalWrite(in1,LOW);  
  }
}

void setMotor2(int dir, int pwmVal, int pwm, int in2){
  analogWrite(pwm,pwmVal); // Motor speed
  if(dir == 1){ 
    // Turn one way
    digitalWrite(in2,HIGH);
  }
  else if(dir == -1){
    // Turn the other way
    digitalWrite(in2,LOW);
  }
  else{
    // Or dont turn
    digitalWrite(in2,LOW);  
  }
}

void setMotor3(int dir, int pwmVal, int pwm, int in3){
  analogWrite(pwm,pwmVal); // Motor speed
  if(dir == 1){ 
    // Turn one way
    digitalWrite(in3,HIGH);
  }
  else if(dir == -1){
    // Turn the other way
    digitalWrite(in3,LOW);
  }
  else{
    // Or dont turn
    digitalWrite(in3,LOW);  
  }
}

void setMotor4(int dir, int pwmVal, int pwm, int in4){
  analogWrite(pwm,pwmVal); // Motor speed
  if(dir == 1){ 
    // Turn one way
    digitalWrite(in4,HIGH);
  }
  else if(dir == -1){
    // Turn the other way
    digitalWrite(in4,LOW);
  }
  else{
    // Or dont turn
    digitalWrite(in4,LOW);  
  }
}

void readEncoder_1(){
  int b = digitalRead(ENCB_1);
  int increment = 0;
  if(b>0){
    increment = 1;
  }
  else{
    increment = -1;
  }
  pos_i = pos_i + increment;

  long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}

void readEncoder_2(){
  int b = digitalRead(ENCB_2);
  int increment = 0;
  if(b>0){
    increment = 1;
  }
  else{
    increment = -1;
  }
  pos_i = pos_i + increment;

  long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}

void readEncoder_3(){
  int b = digitalRead(ENCB_3);
  int increment = 0;
  if(b>0){
    increment = 1;
  }
  else{
    increment = -1;
  }
  pos_i = pos_i + increment;

  long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}

void readEncoder_4(){
  int b = digitalRead(ENCB_4);
  int increment = 0;
  if(b>0){
    increment = 1;
  }
  else{
    increment = -1;
  }
  pos_i = pos_i + increment;

  long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}