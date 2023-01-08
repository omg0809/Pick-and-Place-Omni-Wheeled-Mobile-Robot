#define m1 30
#define m2 31
#define m3 32
#define m4 33

const int ma = 10;
const int mb = 9;
const int mc = 8;
const int md = 7;

int speed = 255;

const int trigPin1 = 40; //front
const int echoPin1 = 41;

const int trigPin2 = 42; //right
const int echoPin2 = 43;

const int trigPin3 = 44; //left
const int echoPin3 = 45;

const int trigPin4 = 46; //back
const int echoPin4 = 47;

long duration1;
long duration2;
long duration3;
long duration4;

int distance1;
int distance2;
int distance3;
int distance4;

void setup() {
pinMode(m1, OUTPUT);
pinMode(m2, OUTPUT);
pinMode(m3, OUTPUT);
pinMode(m4, OUTPUT);

pinMode(trigPin1, OUTPUT); 
pinMode(echoPin1, INPUT);

pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);

pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);

pinMode(trigPin4, OUTPUT);
pinMode(echoPin4, OUTPUT);

Serial.begin(9600); 
}

void loop() {

}

void a1(){
    if(distance1 > 10){
        forward();
    }
    else if(distance1 < 10){
        backward();
    }
    else if(distance1 == 10){
        stopall();
    }
}

void ultra1(){
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1 = duration1*0.034/2;
Serial.print("Distance1: ");
Serial.println(distance1);
}

void ultra2(){
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2 = duration2*0.034/2;
Serial.print("Distance2: ");
Serial.println(distance2);
}

void ultra3(){
digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration3 = pulseIn(echoPin3, HIGH);
distance3 = duration3*0.034/2;
Serial.print("Distance3: ");
Serial.println(distance3);
}

void ultra4(){
digitalWrite(trigPin4, LOW);
delayMicroseconds(2);
digitalWrite(trigPin4, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin4, LOW);
duration4 = pulseIn(echoPin4, HIGH);
distance4 = duration4*0.034/2;
Serial.print("Distance4: ");
Serial.println(distance4);
}

void forward(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(ma, speed);
    analogWrite(mb, speed);
    analogWrite(mc, speed);
    analogWrite(md, speed);
}

void backward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(ma, speed);
    analogWrite(mb, speed);
    analogWrite(mc, speed);
    analogWrite(md, speed);
}

void right_s(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(ma, speed);
    analogWrite(mb, speed);
    analogWrite(mc, speed);
    analogWrite(md, speed);
}

void left_s(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(ma, speed);
    analogWrite(mb, speed);
    analogWrite(mc, speed);
    analogWrite(md, speed);
}

void stopall(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(ma, 0);
    analogWrite(mb, 0);
    analogWrite(mc, 0);
    analogWrite(md, 0);
}

