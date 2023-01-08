#include <Wire.h>
#include <L3G4200D.h>
#include <Servo.h>

L3G4200D gyroscope;

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

int speedA = 250;
int speedB = 250;
int speedC = 250;
int speedD = 250;

int turn_speed = 90;

unsigned long timer = 0;
float timeStep = 0.01;

float yaw = 0;

int target_turn = 0;

char vel;

void setup(){
    Serial.begin(9600);

    Serial.println("Initialize L3G4200D");
    while(!gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_400HZ_50)){
        Serial.println("Could not find a valid L3G4200D sensor, check wiring!");
        delay(500);
    }

    gyroscope.calibrate(100);

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

    if(vel == '0'){
        turn(90);
    }

    if(vel == '9'){
        turn(180);
    }
    
    if(vel == '8'){
        turn(450);
    }
}

void turn(int target){
    yawp();
    gyroscope.calibrate(100);

    while(abs(yaw - target) > 1){
        if(yaw < target){
            left_a();
        }
        if(yaw > target){
            right_a();
        }
        yawp();
    }
}

void yawp(){
    timer = millis();

    Vector norm = gyroscope.readNormalize();

    yaw = yaw + norm.ZAxis * timeStep;

    Serial.print("Yaw = ");
    Serial.println(yaw);

    delay((timeStep*1000) - (millis() - timer));
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
    myservo.write(pos);
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
