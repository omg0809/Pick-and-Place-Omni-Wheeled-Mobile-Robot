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

char vel;

void setup(){
    for(int i=30 ; i<=38 ; i++){
        pinMode(i, OUTPUT);
    }

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
    if(vel == 'h'){
        left_a();
    }
    if(vel == 'k'){
        right_a();
    }
    if(vel == 'y'){
        f_left_d();
    }
    if(vel == 'i'){
        f_right_d();
    }
    if(vel == 'v'){
        b_left_d();
    }
    if(vel == 'n'){
        b_right_d();
    }
}

void forward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    digitalWrite(m5, LOW);
    digitalWrite(m6, LOW);
    digitalWrite(m7, HIGH);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Forward");
}

void backward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    digitalWrite(m5, LOW);
    digitalWrite(m6, LOW);
    digitalWrite(m7, LOW);
    digitalWrite(m8, HIGH);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Backward");
}

void left(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(m5, LOW);
    digitalWrite(m6, HIGH);
    digitalWrite(m7, LOW);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Left");
}

void right(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(m5, HIGH);
    digitalWrite(m6, LOW);
    digitalWrite(m7, LOW);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Right");
}

void right_a(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    digitalWrite(m5, HIGH);
    digitalWrite(m6, LOW);
    digitalWrite(m7, HIGH);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Right_axis");
}

void left_a(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    digitalWrite(m5, LOW);
    digitalWrite(m6, HIGH);
    digitalWrite(m7, LOW);
    digitalWrite(m8, HIGH);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Left_axis");
}

void f_left_d(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    digitalWrite(m5, LOW);
    digitalWrite(m6, HIGH);
    digitalWrite(m7, HIGH);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Forward_left_diagonal");
}

void f_right_d(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    digitalWrite(m5, HIGH);
    digitalWrite(m6, LOW);
    digitalWrite(m7, HIGH);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Forward_right_diagonal");
}

void b_left_d(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    digitalWrite(m5, LOW);
    digitalWrite(m6, HIGH);
    digitalWrite(m7, LOW);
    digitalWrite(m8, HIGH);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Backward_left_diagonal");
}

void b_right_d(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    digitalWrite(m5, HIGH);
    digitalWrite(m6, LOW);
    digitalWrite(m7, LOW);
    digitalWrite(m8, HIGH);
    analogWrite(SpeedAmotor, 220);
    analogWrite(SpeedBmotor, vSpeed);
    analogWrite(SpeedCmotor, vSpeed);
    analogWrite(SpeedDmotor, vSpeed);
    Serial.println("Backward_right_diagonal");
}

void stopall(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(m5, LOW);
    digitalWrite(m6, LOW);
    digitalWrite(m7, LOW);
    digitalWrite(m8, LOW);
    analogWrite(SpeedAmotor, 0);
    analogWrite(SpeedBmotor, 0);
    analogWrite(SpeedCmotor, 0);
    analogWrite(SpeedDmotor, 0);
    Serial.println("stop_all");
}