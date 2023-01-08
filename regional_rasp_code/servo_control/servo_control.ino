#include <Servo.h>

Servo myservo;
int pos = 0;
char val;

void setup() {
  myservo.attach(10);
  Serial.begin(9600);
  myservo.write(0);
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {                  
   val = Serial.read();                  

    switch (val)  {
      case '.':
        increment();
        break;
        
      case '0':
        decrement();
        break;
        
      case '5':
        break;
    }
  }
 
}

void increment()  {
  myservo.write(pos);
  pos++;
  delay(100);
}

void decrement()  {
  myservo.write(pos);
  pos--;
  delay(100);
}