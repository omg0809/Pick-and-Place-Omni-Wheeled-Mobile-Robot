#include<Servo.h>

Servo myservo;
int pos = 0;

const int distance = 100;  //distance in cm
const int wheel_d = 100; //diameter of wheel in mm
const float wheel_c = PI * wheel_d;
const int counts_per_rev = 205;

int motor_offset = 15;

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

int speedA = 160;
int speedB = 160;
int speedC = 160;
int speedD = 160;

const int encd1 = 2;
const int encd2 = 3;
const int encd3 = 18;
const int encd4 = 19;

volatile unsigned long encda = 0;
volatile unsigned long encdb = 0;
volatile unsigned long encdc = 0;
volatile unsigned long encdd = 0;

void setup()
{
    myservo.attach(10);
    myservo.write(15);

    pinMode(encd1, INPUT_PULLUP);
    pinMode(encd2, INPUT_PULLUP);
    pinMode(encd3, INPUT_PULLUP);
    pinMode(encd4, INPUT_PULLUP);

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

    attachInterrupt(digitalPinToInterrupt(encd1), counta, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd2), countb, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd3), countc, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd4), countd, CHANGE);

    brake();
    delay(2000);
    drive_forward(205);
    delay(2000);
    drive_left_a(28);
    delay(2000);
    drive_forward(20);
    delay(2000);
    grip();
    delay(2000);
    drive_backward(20);
    delay(2000);
    drive_left_s(90);
    delay(2000);
    drive_forward(25);
    delay(2000);
    loose();
    delay(2000);
    drive_backward(15);
    delay(2000);
    drive_right_s(97);
    delay(2000);
    drive_forward(18);
    delay(2000);
    grip();
    delay(2000);
    drive_backward(25);
    delay(2000);
    drive_left_a(30);
    delay(2000);
    drive_forward(220);
    delay(2000);
    drive_right_a(30);
    delay(2000);
    drive_forward(20);
    delay(2000);
    brake();

    
}
void loop()
{

}

void drive_forward(float dist){
    encd_reset();

    float num_rev = (dist*10) / wheel_c;
    unsigned long target_tick = num_rev * counts_per_rev;

    while((encda < target_tick) && (encdb < target_tick) && (encdc < target_tick) && (encdd < target_tick)){
        forward();
    }
    brake();
} 

void drive_backward(float dist1){
    encd_reset();

    float num_rev1 = (dist1*10) / wheel_c;
    unsigned long target_tick1 = num_rev1 * counts_per_rev;

    while((encda < target_tick1) && (encdb < target_tick1) && (encdc < target_tick1) && (encdd < target_tick1)){
        backward();
    }
    brake();
}

void drive_left_s(float dist2){
    encd_reset();

    float num_rev2 = (dist2*10) / wheel_c;
    unsigned long target_tick2 = num_rev2 * counts_per_rev;

    while((encda < target_tick2) && (encdb < target_tick2) && (encdc < target_tick2) && (encdd < target_tick2)){
        left_s();
    }
    brake();
}

void drive_right_s(float dist3){
    encd_reset();

    float num_rev3 = (dist3*10) / wheel_c;
    unsigned long target_tick3 = num_rev3 * counts_per_rev;

    while((encda < target_tick3) && (encdb < target_tick3) && (encdc < target_tick3) && (encdd < target_tick3)){
        right_s();
    }
    brake();
}

void drive_left_a(float dist4){
    encd_reset();

    float num_rev4 = (dist4*10) / wheel_c;
    unsigned long target_tick4 = num_rev4 * counts_per_rev;

    while((encda < target_tick4) && (encdb < target_tick4) && (encdc < target_tick4) && (encdd < target_tick4)){
        left_a();
    }
    brake();
}

void drive_right_a(float dist5){
    encd_reset();

    float num_rev5 = (dist5*10) / wheel_c;
    unsigned long target_tick5 = num_rev5 * counts_per_rev;

    while((encda < target_tick5) && (encdb < target_tick5) && (encdc < target_tick5) && (encdd < target_tick5)){
        right_a();
    }
    brake();
}

void encd_reset(){
    encda = 0;
    encdb = 0;
    encdc = 0;
    encdd = 0;
}

void brake()
{
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

void right_a(){
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

void left_a(){
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

void right_s(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speedA);
    analogWrite(motorB, speedB);
    analogWrite(motorC, speedC);
    analogWrite(motorD, 150);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void left_s(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speedA);
    analogWrite(motorB, 150);
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
    for(pos = 15; pos <= 33; pos += 1){
        myservo.write(pos);
        delay(15);
    }
}

void loose(){
    for(pos = 33; pos >= 15; pos -= 1){
        myservo.write(pos);
        delay(15);
    }
}

void counta()
{
    encda++;
}
void countb()
{
    encdb++;
}
void countc()
{
    encdc++;
}
void countd()
{
    encdd++;
}