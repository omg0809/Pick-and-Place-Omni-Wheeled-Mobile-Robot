#include <Wire.h>
#include <L3G4200D.h>

L3G4200D gyroscope;

#define m1 30
#define m2 32
#define m3 34
#define m4 36

const int motorA = 9;
const int motorB = 8;
const int motorC = 7;
const int motorD = 6;

int speed = 200;

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

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);

  stopall();
  
}

void loop()
{
move();
}

void move(){
    yawp();

    if(yaw > 0){
        right_a();
    }
    else if(yaw < 0){
        left_a();
    }
    else if(yaw > 85){
        stopall();
    }
    else if(yaw < 90){
        stopall();
    }
    else{
        stopall();
    }
}

void yawp(){
  timer = millis();

  Vector norm = gyroscope.readNormalize();

  yaw = yaw + norm.ZAxis * timeStep;
  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  delay((timeStep*1000) - (millis() - timer));
}

void forward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void backward(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void right_s(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void left_s(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void right_a(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void left_a(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
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
}
