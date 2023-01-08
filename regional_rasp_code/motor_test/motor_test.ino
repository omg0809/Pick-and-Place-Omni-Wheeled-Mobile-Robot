const int SpeedAmotor = 9;
const int SpeedBmotor = 8;
const int SpeedCmotor = 7;
const int SpeedDmotor = 6;

void setup(){
    pinMode(30, OUTPUT);//m1
    pinMode(32, OUTPUT);//m2
    pinMode(34, OUTPUT);//m3
    pinMode(36, OUTPUT);//m4

    move();
}

void loop(){
    
}

void move(){
    digitalWrite(30, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(34, HIGH);
    digitalWrite(36, LOW);
    analogWrite(SpeedAmotor, 250);
    analogWrite(SpeedBmotor, 250);
    analogWrite(SpeedCmotor, 250);
    analogWrite(SpeedDmotor, 250);
    delay(2000);
}