const int distance = 100;  //distance in cm
const int wheel_d = 100; //diameter of wheel in mm
const float wheel_c = PI * wheel_d;
const int counts_per_rev = 205;

int motor_offset = 15;

#define m1 30
#define m2 32
#define m3 34
#define m4 36

const int motorA = 9;
const int motorB = 8;
const int motorC = 7;
const int motorD = 6;

int speed = 200;

const int encd1 = 2;
const int encd2 = 3;
const int encd3 = 18;
const int encd4 = 19;

volatile unsigned long encda = 0;
volatile unsigned long encdb = 0;
volatile unsigned long encdc = 0;
volatile unsigned long encdd = 0;

float diffL;
float diffR;

void setup()
{
    pinMode(encd1, INPUT_PULLUP);
    pinMode(encd2, INPUT_PULLUP);
    pinMode(encd3, INPUT_PULLUP);
    pinMode(encd4, INPUT_PULLUP);

    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m3, OUTPUT);
    pinMode(m4, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(encd1), counta, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd2), countb, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd3), countc, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd4), countd, CHANGE);

    brake();
    delay(1000);
    drive(100);
    delay(1000);
    brake();
}
void loop()
{

}

void drive(float dist)
{
    float num_rev = (dist*10) / wheel_c;
    unsigned long target_tick = num_rev * counts_per_rev;

    while((encda < target_tick) && (encdb < target_tick) && (encdc < target_tick) && (encdd < target_tick)){
        forward();
    }
    brake();
}



void brake()
{
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
    analogWrite(motorC, 0);
    analogWrite(motorD, 0);
}

void forward()
{
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void backward()
{
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void right_s(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void left_s(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
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