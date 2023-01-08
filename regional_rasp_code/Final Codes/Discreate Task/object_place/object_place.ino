#include<Servo.h>

Servo myservo;
int pos = 0;

#define m1 30
#define m2 32
#define m3 34
#define m4 36

#define m5 38
#define m6 40

#define gled 22
#define rled 24

const int motorA = 9;
const int motorB = 8;
const int motorC = 7;
const int motorD = 6;

int speedA = 200;
int speedB = 200;
int speedC = 190;
int speedD = 190;

void setup(){
    myservo.attach(10);
    myservo.write(0);

    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m3, OUTPUT);
    pinMode(m4, OUTPUT);

    pinMode(m5, OUTPUT);
    pinMode(m6, OUTPUT);

    pinMode(gled, OUTPUT);
    digitalWrite(gled, LOW);
    pinMode(rled, OUTPUT);
    digitalWrite(rled, HIGH);

    stopall();
    delay(1000);
    forward();
    delay(100);
    grip();
    delay(1000);
    backward();
    delay(100);
    stopall();
}

void loop(){

}

void forward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speedA);
    analogWrite(motorB, speedB);
    analogWrite(motorC, speedC);
    analogWrite(motorD, speedD);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void backward(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speedA);
    analogWrite(motorB, speedB);
    analogWrite(motorC, speedC);
    analogWrite(motorD, speedD);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void up(){
    digitalWrite(m5, HIGH);
    digitalWrite(m6, LOW);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void down(){
    digitalWrite(m5, LOW);
    digitalWrite(m6, HIGH);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void stopall(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(m5, LOW);
    digitalWrite(m6, LOW);
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
    analogWrite(motorC, 0);
    analogWrite(motorD, 0);

    digitalWrite(gled, LOW);
    digitalWrite(rled, HIGH);
}


void grip(){
    for (pos = 0; pos <= 45; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}

void loose(){
    for (pos = 45; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}