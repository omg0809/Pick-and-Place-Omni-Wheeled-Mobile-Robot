const int distance = 100;
const int wheel_d = 100;
const float wheel_c = PI * wheel_d;
const int counts_per_rev = 430;

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

const int trigPin_f = 44;
const int echoPin_f = 45;

const int trigPin_l = 42;
const int echoPin_l = 43;

const int trigPin_r = 47;
const int echoPin_r = 46;

long duration_f;
int distance_f;

long duration_l;
int distance_l;

long duration_r;
int distance_r;

void setup() {

    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m3, OUTPUT);
    pinMode(m4, OUTPUT);

    pinMode(encd1, INPUT_PULLUP);
    pinMode(encd2, INPUT_PULLUP);
    pinMode(encd3, INPUT_PULLUP);
    pinMode(encd4, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(encd1), counta, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd2), countb, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd3), countc, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encd4), countd, CHANGE);

    pinMode(trigPin_f, OUTPUT);
    pinMode(echoPin_f, INPUT);

    pinMode(trigPin_l, OUTPUT);
    pinMode(echoPin_l, INPUT);

    pinMode(trigPin_r, OUTPUT);
    pinMode(echoPin_r, INPUT);

    Serial.begin(9600); 

    brake();
    delay(2000);

    //drive_forward(100);
    //brake();

    //drive_backward(100);
    //brake();

}

void loop() {
    a_f();
}

void drive_forward(float dist){
    encd_reset();

    float num_rev = (dist * 10) / wheel_c;
    unsigned long target_tick = num_rev * counts_per_rev;

    while((encda < target_tick) && (encdb < target_tick) && (encdc < target_tick) && (encdd < target_tick)){
        forward();
    }
    brake();
}

void drive_backward(float dist2){
    encd_reset();

    float num_rev2 = (dist2 * 10) / wheel_c;
    unsigned long target_tick2 = num_rev2 * counts_per_rev;

    while((encda < target_tick2) && (encdb < target_tick2) && (encdc < target_tick2) && (encdd < target_tick2)){
        backward();
    }
    brake();
}

void drive_right_s(float dist1){
    encd_reset();

    float num_rev1 = (dist1 * 10) / wheel_c;
    unsigned long target_tick1 = num_rev1 * counts_per_rev;

    while((encda < target_tick1) && (encdb < target_tick1) && (encdc < target_tick1) && (encdd < target_tick1)){
        right_s();
    }
    brake();
}

void drive_left_s(float dist3){
    encd_reset();

    float num_rev3 = (dist3 * 10) / wheel_c;
    unsigned long target_tick3 = num_rev3 * counts_per_rev;

    while((encda < target_tick3) && (encdb < target_tick3) && (encdc < target_tick3) && (encdd < target_tick3)){
        left_s();
    }
    brake();
}


void a_f(){
    ultra_f();
    
    while(distance_f == 15){
        forward();
    }
    brake();
}

void a_r(){
    ultra_r();

    if(distance_r > 15){
        right_s();
    }
    else if(distance_r < 15){
        left_s();
    }
    else if(distance_r == 15){
        brake();
    }
    else{
        brake();
    }
}

void a_l(){
    ultra_l();

    if(distance_l > 15){
        left_s();
    }
    else if(distance_l < 15){
        right_s();
    }
    else if(distance_l == 15){
        brake();
    }
    else{
        brake();
    }
}

void ultra_r(){
    digitalWrite(trigPin_r, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_r, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_r, LOW);
    duration_r = pulseIn(echoPin_r, HIGH);
    distance_r = duration_r * 0.034/2;
    Serial.print("Distance Left: ");
    Serial.println(distance_r);
}

void ultra_l(){
    digitalWrite(trigPin_l, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_l, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_l, LOW);
    duration_l = pulseIn(echoPin_l, HIGH);
    distance_l = duration_l * 0.034/2;
    Serial.print("Distance Left: ");
    Serial.println(distance_l);
}

void ultra_f(){
    digitalWrite(trigPin_f, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_f, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_f, LOW);
    duration_f = pulseIn(echoPin_f, HIGH);
    distance_f = duration_f * 0.034/2;
    Serial.print("Distance Front: ");
    Serial.println(distance_f);
}

void forward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
}

void backward(){
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

void right_a(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(motorA, speed);
    analogWrite(motorB, speed);
    analogWrite(motorC, speed);
    analogWrite(motorD, speed);
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
}

void brake(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
    analogWrite(motorC, 0);
    analogWrite(motorD, 0);
}

void encd_reset(){
    encda = 0;
    encdb = 0;
    encdc = 0;
    encdd = 0;
}

void counta(){
    encda++;
}

void countb(){
    encdb++;
}

void countc(){
    encdc++;
}

void countd(){
    encdd++;
}