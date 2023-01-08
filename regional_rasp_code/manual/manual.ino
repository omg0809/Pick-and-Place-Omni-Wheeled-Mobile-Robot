#define m1 30
#define m2 31
#define m3 32
#define m4 33

const int SpeedAmotor = 9;
const int SpeedBmotor = 8;

int vSpeed = 255;

char vel;

void setup(){
    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m3, OUTPUT);
    pinMode(m4, OUTPUT);
    
    Serial.begin(9600);
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
        right();
    }
    if(vel == 'l'){
        left();
    }
    if(vel == 's'){
        stopall();
    }
}

void forward(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
}

void backward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
}

void right(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
}

void left(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
}

void stopall(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(SpeedAmotor, 0);
    analogWrite(SpeedBmotor, 0);
}