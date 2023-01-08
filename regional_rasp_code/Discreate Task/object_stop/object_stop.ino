#define m1 38
#define m2 40

#define gled 12
#define rled 11

const int trigPin = 48;
const int echoPin = 49;

long duration;
int distance;

void setup(){
    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);

    pinMode(gled, OUTPUT);
    digitalWrite(gled, LOW);
    pinMode(rled, OUTPUT);
    digitalWrite(rled, HIGH);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);
}

void loop(){
    ultra();

    if(distance > 5){
        up();
    }
    else if(distance < 5){
        stopall();
    }
    else{
        
    }
}

void ultra(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);
}

void up(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void down(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void stopall(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    
    digitalWrite(gled, LOW);
    digitalWrite(rled, HIGH);
}

