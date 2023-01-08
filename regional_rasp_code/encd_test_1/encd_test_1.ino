#define m1 30
#define m2 32
#define m3 34

const int PWM_A = 7;
const int PWM_B = 6;
const int PWM_C = 5;

const int encd_A = 2;
const int encd_B = 18;
const int encd_C = 20;

int target = 500;

int target1 = 500;

volatile unsigned long encdA = 0;
volatile unsigned long encdB = 0;
volatile unsigned long encdC = 0;

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
  delay(1000);
  driveB();
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
  backward();
  delay(20);
  brake();
}

void driveB(){
  encdA = 0;
  encdB = 0;

  while((encdA < target1) && (encdB < target1)){
    backward();

    delay(20);

    if(encdA>encdB){
        analogWrite(PWM_A, 0);
    }
    else if(encdB>encdA){
        analogWrite(PWM_B, 0);
    }
  }
  
  brake();
  forward();
  delay(20);
  brake();
}

void brake(){
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  analogWrite(PWM_A, 0);
  analogWrite(PWM_B, 0);
  analogWrite(PWM_C, 0);
}

void forward(){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  analogWrite(PWM_A, 250);
  analogWrite(PWM_B, 250);
  analogWrite(PWM_C, 0);
}

void backward(){
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  analogWrite(PWM_A, 250);
  analogWrite(PWM_B, 250);
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
