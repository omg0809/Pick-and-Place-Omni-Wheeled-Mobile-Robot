#define m1 30
#define m2 32
#define m3 34
#define m4 36

const int motorA = 9;
const int motorB = 8;
const int motorC = 7;
const int motorD = 6;

int speed = 200;

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

    pinMode(trigPin_f, OUTPUT); 
    pinMode(echoPin_f, INPUT); 

    pinMode(trigPin_l, OUTPUT);
    pinMode(echoPin_l, INPUT);

    pinMode(trigPin_r, OUTPUT);
    pinMode(echoPin_r, INPUT);

    Serial.begin(9600); 

}

void loop() {
    a_r();
}

void a_f(){
    ultra_f();
    
    if(distance_f > 15){
        forward();
    }
    else if(distance_f < 15){
        backward();
    }
    else if(distance_f == 15){
        stopall();
    }
    else{
        stopall();
    }
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
        stopall();
    }
    else{
        stopall();
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
        stopall();
    }
    else{
        stopall();
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

void stopall(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, HIGH);
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
    analogWrite(motorC, 0);
    analogWrite(motorD, 0);
}
