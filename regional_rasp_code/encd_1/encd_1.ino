#define m1 30
#define m2 32
#define m3 34

const int PWM_A = 9;
const int PWM_B = 8;
const int PWM_C = 7;

const int encd_A = 18;
const int encd_B = 2;
const int encd_C = 20;

int target = 500;

volatile unsigned long encd_a = 0;
volatile unsigned long encd_b = 0;
volatile unsigned long encd_c = 0;

void setup(){
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
  drive();
}

void loop(){

}

void drive() {
  while ( (encd_a < target) && (encd_b < target) ) {
      forward();
  }
  brake();
}

void forward(){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  analogWrite(PWM_A, 250);
  analogWrite(PWM_B, 250);
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
  encd_a++;
}

void countB(){
  encd_b++;
}

void countC(){
  encd_c++;
}
