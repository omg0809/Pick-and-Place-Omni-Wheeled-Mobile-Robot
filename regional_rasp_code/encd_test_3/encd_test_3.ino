#define m1 30
#define m2 32
#define m3 34

const int PWM_A = 5;
const int PWM_B = 6;
const int PWM_C = 7;

int mspeed = 250;

const int encd_A = 18;
const int encd_B = 2;
const int encd_C = 20;

volatile unsigned long encdA = 0;
volatile unsigned long encdB = 0;
volatile unsigned long encdC = 0;

int target = 400;

void setup(){

  Serial.begin(9600);
  pinMode(encd_A, INPUT_PULLUP);
  pinMode(encd_B, INPUT_PULLUP);
  pinMode(encd_C, INPUT_PULLUP);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(encd_A), countA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encd_B), countB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encd_C), countC, CHANGE);

  brake();
  delay(1000);
  driveF();
}

void loop(){

}

void driveF(){
  while((encdA < target) && (encdB < target)){
    forward();
    delay(20);

    if(encdA>encdB){
        analogWrite(PWM_A, 0);
    }
    else if(encdB>encdA){
        analogWrite(PWM_B, 0);
    }
  }
  
  brake();
}

void forward(){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  analogWrite(PWM_A, mspeed);
  analogWrite(PWM_B, mspeed);
  analogWrite(PWM_C, 0);
}

void brake(){
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  analogWrite(PWM_A, 0);
  analogWrite(PWM_B, 0);
  analogWrite(PWM_C, 0);
}

void countA(){
  encdA++;
}

void countB(){
  encdB++;
}

void countC(){
  encdC++;
}
