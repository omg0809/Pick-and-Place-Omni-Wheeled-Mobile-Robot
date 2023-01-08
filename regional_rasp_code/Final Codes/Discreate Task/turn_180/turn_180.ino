#include <Wire.h>
#include <L3G4200D.h>

L3G4200D gyroscope;

#define m1 30
#define m2 32
#define m3 34
#define m4 36

#define gled 12
#define rled 11

const int motorA = 9;
const int motorB = 8;
const int motorC = 7;
const int motorD = 6;

int speed = 90;

unsigned long timer = 0;
float timeStep = 0.01;

float yaw = 0;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize L3G4200D");

  while(!gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_400HZ_50))
  {
    Serial.println("Could not find a valid L3G4200D sensor, check wiring!");
    delay(500);
  }

  gyroscope.calibrate(100);

  //gyroscope.setThreshold(3);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);

  pinMode(gled, OUTPUT);
  digitalWrite(gled, LOW);
  pinMode(rled, OUTPUT);
  digitalWrite(rled, HIGH);
  
  turn(150);
}

void loop(){
}

void turn(int target){
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
    stopall();
}

void yawp(){
  timer = millis();

  Vector norm = gyroscope.readNormalize();

  yaw = yaw + norm.ZAxis * timeStep;
  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  delay((timeStep*1000) - (millis() - timer));
}

void right_a(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void left_a(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void stopall(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
    analogWrite(motorC, 0);
    analogWrite(motorD, 0);

    digitalWrite(gled, LOW);
    digitalWrite(rled, HIGH);
}
