#define m1 30
#define m2 32
#define m3 34

const int SpeedAmotor = 9;
const int SpeedBmotor = 8;
const int SpeedCmotor = 7;

int move = 180;
int stop = 0;

char vel;

void setup(){
    for(int i = 0 ; i<=35 ; i++){
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
        right_a();
    }

    if(vel == 'l'){
        left_a();
    }

    if(vel == 'q'){
        right_s();
    }

    if(vel == 'e'){
        left_s();
    }

    if(vel == 'u'){
        f_right_d();
    }
    
    if(vel == 't'){
        f_left_d();
    }

    if(vel == 'v'){
        b_left_d();
    }
    
    if(vel == 'n'){
        b_right_d();
    }

    if(vel == 's'){
        stopAll();
    }
}

void right_a(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    analogWrite(SpeedAmotor, move);
    analogWrite(SpeedBmotor, move);
    analogWrite(SpeedCmotor, move);
}

void left_a(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    analogWrite(SpeedAmotor, move);
    analogWrite(SpeedBmotor, move);
    analogWrite(SpeedCmotor, move);
}

void right_s(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    analogWrite(SpeedAmotor, 105);
    analogWrite(SpeedBmotor, 105);
    analogWrite(SpeedCmotor, 155);
}

void left_s(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    analogWrite(SpeedAmotor, 105);
    analogWrite(SpeedBmotor, 105);
    analogWrite(SpeedCmotor, 155);
}

void f_right_d(){
    digitalWrite(m1, HIGH);
    //digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    analogWrite(SpeedAmotor, 250);
    analogWrite(SpeedBmotor, 0);
    analogWrite(SpeedCmotor, 250);
}

void b_right_d(){
    digitalWrite(m1, LOW);
    //digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    analogWrite(SpeedAmotor, 250);
    analogWrite(SpeedBmotor, 0);
    analogWrite(SpeedCmotor, 250);
}

void f_left_d(){
    //digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    analogWrite(SpeedAmotor, 0);
    analogWrite(SpeedBmotor, 250);
    analogWrite(SpeedCmotor, 250);
}

void b_left_d(){
    //digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    analogWrite(SpeedAmotor, 0);
    analogWrite(SpeedBmotor, 250);
    analogWrite(SpeedCmotor, 250);
}

void forward(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    analogWrite(SpeedAmotor, move);
    analogWrite(SpeedBmotor, move);
    analogWrite(SpeedCmotor, stop);
}

void backward(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    analogWrite(SpeedAmotor, move);
    analogWrite(SpeedBmotor, move);
    analogWrite(SpeedCmotor, stop);
}

void stopAll(){
    analogWrite(SpeedAmotor, stop);
    analogWrite(SpeedBmotor, stop);
    analogWrite(SpeedCmotor, stop);
}