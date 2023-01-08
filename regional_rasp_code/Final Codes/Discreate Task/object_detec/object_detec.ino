#define m1 38
#define m2 40

#define gled 22
#define rled 24

char vel;

void setup(){
    Serial.begin(9600);

    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);

    pinMode(gled, OUTPUT);
    digitalWrite(gled, LOW);
    pinMode(rled, OUTPUT);
    digitalWrite(rled, HIGH);

    stopall();
}

void loop(){
    if(Serial.available() > 0){
        vel = Serial.read();
    }

    if(vel == '1'){
        lower();
    }

    if(vel == '2'){
        middle();
    }

    if(vel == '3'){
        top();
    }

    if(vel == 'z'){
        up();
    }

    if(vel == 'c'){
        down();
    }

    if(vel == 'x'){
        stopall();
    }

}

void up(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void down(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);

    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
}

void found(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);

    digitalWrite(rled, HIGH);
    delay(1000);
    digitalWrite(rled, LOW);
    delay(1000);
    digitalWrite(gled, HIGH);
    delay(1000);
    digitalWrite(gled, LOW);
    delay(1000);
}

void stopall(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);

    digitalWrite(gled, LOW);
    digitalWrite(rled, HIGH);
}

void lower(){
    up();
    delay(4500);
    found();
}

void middle(){
    up();
    delay(12000);
    found();
}

void top(){
    up();
    delay(18500);
    found();
}