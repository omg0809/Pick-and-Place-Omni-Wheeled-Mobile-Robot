// This alternate version of the code does not require
// atomic.h. Instead, interrupts() and noInterrupts() 
// are used. Please use this code if your 
// platform does not support ATOMIC_BLOCK.

// Pins
#define ENCA_1 2
#define ENCB_1 31
#define ENCA_2 3
#define ENCB_2 33
#define ENCA_3 18
#define ENCB_3 35
#define ENCA_4 19
#define ENCB_4 37

#define PWM_1 9
#define PWM_2 8
#define PWM_3 7
#define PWM_4 6

#define IN1 30
#define IN2 32
#define IN3 34
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
long currT = micros();

float eintegral = 0;
float vt = 100*(sin(currT/1e6)>0);

float kp = 5;
float ki = 10;
float e = vt-v1Filt;
float u = kp*e + ki*eintegral;

int pos = 0;
float velocity2 = 0;

// turn interrupts back on

  // Compute velocity with method 1

float deltaT = ((float) (currT-prevT))/1.0e6;
float velocity1 = (pos - posPrev)/deltaT;


float v1 = velocity1/600.0*60.0;
float v2 = velocity2/600.0*60.0;

void setup() {
  Serial.begin(115200);

  pinMode(ENCA_1,INPUT);
  pinMode(ENCB_1,INPUT);
  pinMode(ENCA_2,INPUT);
  pinMode(ENCB_2,INPUT);
  pinMode(ENCA_3,INPUT);
  pinMode(ENCB_3,INPUT);
  pinMode(ENCA_4,INPUT);
  pinMode(ENCB_4,INPUT);

  pinMode(PWM_1,OUTPUT);
  pinMode(PWM_2,OUTPUT);
  pinMode(PWM_3,OUTPUT);
  pinMode(PWM_4,OUTPUT);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA_1),readEncoder,RISING);
}

void loop() {

  // read the position and velocity
  
  
  // Set the motor speed and direction
  int dir = 1;
  if (u<0){
    dir = -1;
  int pwr = (int) fabs(u);
  if(pwr > 255){
    pwr = 255;
  }
  setMotorA(dir,pwr,PWM_1,IN1);
}
}

void setMotorA(int dir, int pwmVal, int pwm, int in1){
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
  
  
noInterrupts(); // disable interrupts temporarily while reading
pos = pos_i;
velocity2 = velocity_i;
interrupts(); 

  // Convert count/s to RPM
  posPrev = pos;
prevT = currT;

  // Low-pass filter (25 Hz cutoff)
  v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  v1Prev = v1;
  v2Filt = 0.854*v2Filt + 0.0728*v2 + 0.0728*v2Prev;
  v2Prev = v2;

  // Set a target
  long currT = micros();


  // Compute the control signal u
  
  float e = vt-v1Filt;
  eintegral = eintegral + e*deltaT;
}

void readEncoder(){
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