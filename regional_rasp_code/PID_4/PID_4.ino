#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA 2 // YELLOW
#define ENCB 4 // WHITE
#define PWM 9
#define IN1 30

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
}

void loop() {
  
  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }

  setMotor(1, 125, PWM, IN1);
  delay(2000);
  Serial.println(pos);
  setMotor(-1, 125, PWM, IN1);
  delay(2000);
  Serial.println(pos);
  setMotor(0, 125, PWM, IN1);
  delay(200);
  Serial.println(pos);
}

void setMotor(int dir, int pwmVal, int pwm, int in1){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
  }
  else{
    digitalWrite(in1,LOW);
  }
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}
