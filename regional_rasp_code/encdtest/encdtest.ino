const int encd = 3;

volatile unsigned long encda = 0;

void setup(){
    Serial.begin(9600);

    pinMode(encd, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(encd), count, CHANGE);
}

void loop(){
    Serial.println(encda);
}

void count(){
    encda++;
}