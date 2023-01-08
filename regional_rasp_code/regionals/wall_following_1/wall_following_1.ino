#define m1 30
#define m2 31
#define m3 32
#define m4 33
#define m5 34
#define m6 35
#define m7 36
#define m8 37

const int SpeedAmotor = 9;
const int SpeedBmotor = 8;
const int SpeedCmotor = 7;
const int SpeedDmotor = 10;

int vSpeed = 180;

#define trigr 48
#define echor 49
long durationr;
int distancer;

#define trigl 51
#define echol 50
long durationl;
int distancel;

#define trigf 53
#define echof 52
long durationf;
int distancef;

void setup(){
    for(int i=30 ; i<=38 ; i++){
        pinMode(i, OUTPUT);
    }

    pinMode(trigr, OUTPUT);
    pinMode(echor, INPUT);
    
    pinMode(trigl, OUTPUT);
    pinMode(echol, INPUT);

    pinMode(trigf, OUTPUT);
    pinMode(echof, INPUT);

    Serial.begin(9600);
}

void loop(){
    ultrar();
    ultral();
    ultraf();

    if(distancel>10 && distancef>10 && distancer<10){
        forward();
    }
    else if(distancel>10 && distancef<10 && distancer>10){
        stopall();
    }
    else if(distancel<10 && distancef>10 && distancer>10){
        forward();
    }
    else if(distancel>10 && distancef<10 && distancer<10){
        left();
    }
    else if(distancel<10 && distancef<10 && distancer>10){
        right();
    }
    else if(distancel<10 && distancef>10 && distancer<10){
        forward();
    }
    else{
        stopall();
    }

}

void forward(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    digitalWrite(m5, HIGH);
    digitalWrite(m6, LOW);
    digitalWrite(m7, HIGH);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Forward");
}

void backward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    digitalWrite(m5, LOW);
    digitalWrite(m6, HIGH);
    digitalWrite(m7, LOW);
    digitalWrite(m8, HIGH);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Backward");
}

void left(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    digitalWrite(m5, LOW);
    digitalWrite(m6, HIGH);
    digitalWrite(m7, HIGH);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Left");
}

void right(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    digitalWrite(m5, HIGH);
    digitalWrite(m6, LOW);
    digitalWrite(m7, LOW);
    digitalWrite(m8, HIGH);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("right");
}

void stopall(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    analogWrite(SpeedAmotor, vSpeed);
    analogWrite(SpeedBmotor, vSpeed);
    Serial.println("Stop");
}

void ultrar(){
    digitalWrite(trigr, LOW);
    delayMicroseconds(2); 
    digitalWrite(trigr, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigr, LOW);
    durationr = pulseIn(echor, HIGH);
    distancer = (durationr / 2) / 29.1;
    digitalWrite(trigr, LOW);  
    Serial.print("Right Distance: ");
    Serial.println(distancer);
}

void ultral(){
    digitalWrite(trigl, LOW);
    delayMicroseconds(2); 
    digitalWrite(trigl, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigl, LOW);
    durationl = pulseIn(echol, HIGH);
    distancel = (durationl / 2) / 29.1;
    digitalWrite(trigl, LOW);  
    Serial.print("Left Distance: ");
    Serial.println(distancel);
}

void ultraf(){
    digitalWrite(trigf, LOW);
    delayMicroseconds(2); 
    digitalWrite(trigf, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigf, LOW);
    durationf = pulseIn(echof, HIGH);
    distancef = (durationf / 2) / 29.1;
    digitalWrite(trigf, LOW);  
    Serial.print("Front Distance: ");
    Serial.println(distancef);
}