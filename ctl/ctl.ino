#include<PID_v1.h>

#define m1 30
#define m2 32
#define m3 34
#define m4 36

const int pwm1 = 9;
const int pwm2 = 8;
const int pwm3 = 7;
const int pwm4 = 6;

volatile int motor1Count = 0;
int encd1A = 22;
int encd1B = 23;

volatile int motor2Count = 0;
int encd2A = 24;
int encd2B = 25;

volatile int motor3Count = 0;
int encd3A = 26;
int encd3B = 27;

volatile int motor4Count = 0;
int encd4A = 28;
int encd4B = 29;

double kp=00.00, ki=00.00, kd=00.00;

double SetPointRotate;
double targetRotate;

double Setpoint1, Input1, Output1, SetpointMove1;
PID pid1(&Input1, &Output1, &Setpoint1, kp, ki, kd, DIRECT);

double Setpoint2, Input2, Output2, SetpointMove2;
PID pid2(&Input2, &Output2, &Setpoint2, kp, ki, kd, DIRECT);

double Setpoint3, Input3, Output3, SetpointMove3;
PID pid3(&Input3, &Output3, &Setpoint3, kp, ki, kd, DIRECT);

double Setpoint4, Input4, Output4, SetpointMove4;
PID pid4(&Input4, &Output4, &Setpoint4, kp, ki, kd, DIRECT);

double SetpointR, InputR, OutputR;
double kpR = 00.00, kiR = 00.00, kdR = 00.00;
PID pidR (&InputR, &OutputR, &SetpointR, kpR, kiR, kdR, DIRECT);

unsigned long previousMicros;
int motorUpdateTime = 0;
int batteryUpdateTime = 0;
int count = 0;

void setup(){
    Serial.begin(115200);

    pinMode(encd1A, INPUT);
    pinMode(encd1B, INPUT);
    pinMode(encd2A, INPUT);
    pinMode(encd2B, INPUT);
    pinMode(encd3A, INPUT);
    pinMode(encd3B, INPUT);
    pinMode(encd4A, INPUT);
    pinMode(encd4B, INPUT);

    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m3, OUTPUT);
    pinMode(m4, OUTPUT);

    attachInterrupt(encd1A, motor1interuptA, CHANGE);
    attachInterrupt(encd1B, motor1interuptB, CHANGE);
    attachInterrupt(encd2A, motor2interuptA, CHANGE);
    attachInterrupt(encd2B, motor2interuptB, CHANGE);
    attachInterrupt(encd3A, motor3interuptA, CHANGE);
    attachInterrupt(encd3B, motor3interuptB, CHANGE);
    attachInterrupt(encd4A, motor4interuptA, CHANGE);
    attachInterrupt(encd4B, motor4interuptB, CHANGE);

    previousMicros = 0;
    targetRotate = 0;

    pid1.SetMode(AUTOMATIC);
    pid1.SetOutputLimits(-255,255);
    Setpoint1 = 0;
    SetpointMove1 = 0;

    pid2.SetMode(AUTOMATIC);
    pid2.SetOutputLimits(-255,255);
    Setpoint2 = 0;
    SetpointMove2 = 0;

    pid3.SetMode(AUTOMATIC);
    pid3.SetOutputLimits(-255,255);
    Setpoint3 = 0;
    SetpointMove3 = 0;

    pid4.SetMode(AUTOMATIC);
    pid4.SetOutputLimits(-255,255);
    Setpoint4 = 0;
    SetpointMove4 = 0;

    pidR.SetMode(AUTOMATIC);
    pidR.SetOutputLimits(-1.5,1.5);

    analogWrite(pwm1, 0);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, 0);
    analogWrite(pwm4, 0);
}

void loop(){

    unsigned long currentMicros = micros();
    float timeElapsed = currentMicros - previousMicros;
    previousMicros = currentMicros;

    motorUpdateTime += timeElapsed;
    batteryUpdateTime += timeElapsed;

    if(motorUpdateTime > 10000){
        unsigned long error = 123;
    }
}