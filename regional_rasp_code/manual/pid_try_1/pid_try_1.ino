int kp = 3;
int ki = 2;
int kd = 1;

PID myPID(&difference, &driverOut, &setPoint,kp,ki,kd, DIRECT);

void setup(){
    myPID.SetMode(AUTOMATIC);

    attachInterrupt(digitalPinToInterrupt(2), blink, CHANGE);
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(30, HIGH);
    digitalWrite(31, LOW);
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(9600);
}

void loop(){
    myPID.Compute();
    analogWrite(30, driveOut);
    Serial.print(" difference: "); Serial.print(difference); Serial.print(" ");
    Serial.print("setPoint: "); Serial.print(setPoint); Serial.print(" ");
    Serial.print("driverOut: "); Serial.println(driverOut);
    digitalWrite(LED_BUILTIN, LOW);
    recvOneChar();
}