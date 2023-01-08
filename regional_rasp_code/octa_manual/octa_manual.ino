#include <Servo.h>

Servo myservo;
int pos = 15;

#define m1 30
#define m2 32
#define m3 34
#define m4 36

#define m5 38
#define m6 40

#define gled 12
#define rled 11

const int motorA = 9;
const int motorB = 8;
const int motorC = 7;
const int motorD = 6;

int speedA = 200;
int speedB = 200;
int speedC = 190;
int speedD = 190;

char vel;

void setup(){
    Serial.begin(9600);
    myservo.attach(10);
    myservo.write(pos);
    delay(1000);

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
}

void loop(){
    if(Serial.available()>0){
        vel = Serial.read();
    }
    if(vel == 'f'){
        forward();
    }

    if(vel == 'b'){
        backward();
    }

    if(vel == 'r'){
        right_s();
    }

    if(vel == 'l'){
        left_s();
    }

    if(vel == 'q'){
        right_a();
    }

    if(vel == 'e'){
        left_a();
    }

    if(vel == 'z'){
        up();
    }

    if(vel == 'c'){
        down();
    }

    if(vel == 's'){
        stopall();
    }
    if(vel == '1'){
        grip();
    }
    if(vel == '2'){
        loose();
    }
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

void right_s(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speedA);
    analogWrite(motorB, speedB);
    analogWrite(motorC, speedC);
    analogWrite(motorD, speedD);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void left_s(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speedA);
    analogWrite(motorB, speedB);
    analogWrite(motorC, speedC);
    analogWrite(motorD, speedD);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void right_a(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speedA);
    analogWrite(motorB, speedB);
    analogWrite(motorC, speedC);
    analogWrite(motorD, speedD);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void left_a(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speedA);
    analogWrite(motorB, speedB);
    analogWrite(motorC, speedC);
    analogWrite(motorD, speedD);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void up(){
    digitalWrite(m5, LOW);
    digitalWrite(m6, HIGH);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void down(){
    digitalWrite(m5, HIGH);
    digitalWrite(m6, LOW);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void grip(){
   myservo.write(pos);
   pos++;
    delay(10);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void loose(){
    myservo.write(25);
    pos--;
    delay(10);

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
