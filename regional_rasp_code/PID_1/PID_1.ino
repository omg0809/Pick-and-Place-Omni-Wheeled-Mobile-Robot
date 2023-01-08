#include <util/atomic.h>

// m1
#define ENCA_1 2
#define ENCB_1 31
#define PWM_1 9
#define IN1 30

//m2
#define ENCA_2 3
#define ENCB_2 33
#define PWM_2 8
#define IN2 32

//m3
#define ENCA_3 18
#define ENCB_3 35
#define PWM_3 7
#define IN3 34

//m4
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
float v3Filt = 0;
float v3Prev = 0;
float v4Filt = 0;
float v4Prev = 0;

float eintegral = 0;

void setup() {
  Serial.begin(115200);

  //m1  
  pinMode(ENCA_1,INPUT);
  pinMode(ENCB_1,INPUT);
  pinMode(PWM_1,OUTPUT);
  pinMode(IN1,OUTPUT);

  //m2
  pinMode(ENCA_2, INPUT);
  pinMode(ENCB_2, INPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(IN2, OUTPUT);

  //m3
  pinMode(ENCA_3, INPUT);
  pinMode(ENCB_3, INPUT);
  pinMode(PWM_3, OUTPUT);
  pinMode(IN3, OUTPUT);

  //m4
  pinMode(ENCA_4, INPUT);
  pinMode(ENCB_4, INPUT);
  pinMode(PWM_4, OUTPUT);
  pinMode(IN4, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA_1),readEncoderA,RISING);

}

void loop() {

  // read the position in an atomic block
  // to avoid potential misreads
  int pos = 0;
  float velocity2 = 0;
  float velocity4 = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    pos = pos_i;
    velocity2 = velocity_i;
    velocity4 = velocity_i;
  }

  // Compute velocity with method 1
  long currT = micros();
  float deltaT = ((float) (currT-prevT))/1.0e6;
  float velocity1 = (pos - posPrev)/deltaT;
  float velocity3 = (pos - posPrev)/deltaT;
  posPrev = pos;
  prevT = currT;

  // Convert count/s to RPM
  float v1 = velocity1/600.0*60.0;
  float v2 = velocity2/600.0*60.0;
  float v3 = velocity3/600.0*60.0;
  float v4 = velocity4/600.0*60.0;

  // Low-pass filter (25 Hz cutoff)
  v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  v1Prev = v1;
  v2Filt = 0.854*v2Filt + 0.0728*v2 + 0.0728*v2Prev;
  v2Prev = v2;
  v3Filt = 0.854*v3Filt + 0.0728*v3 + 0.0728*v3Prev;
  v3Prev = v3;
  v4Filt = 0.854*v4Filt + 0.0728*v4 + 0.0728*v4Prev;
  v4Prev = v4;

  // Set a target
  float vt = 255;

  // Compute the control signal u
  float kp = 1;
  float ki = 5;
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
  setMotor(dir,pwr,PWM_1,IN1);
  setMotor(-1, pwr, PWM_2, IN2);
  setMotor(-1, pwr, PWM_3, IN3);
  setMotor(dir, pwr, PWM_4, IN4);

  Serial.print(vt);
  Serial.print(" ");
  Serial.print(v1Filt);
  Serial.println();
  delay(1);
}

void setMotor(int dir, int pwmVal, int pwm, int in1){
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
    analogWrite(PWM_1,0);   
  }
}

void readEncoderA(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENCB_1);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  pos_i = pos_i + increment;

  // Compute velocity with method 2
  long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}
