#define encoder0PinA 18      // encoder 1
#define encoder0PinB 19

#define encoder1PinA 20     // encoder 2
#define encoder1PinB 21

#define encoder2PinA 2      // encoder 3
#define encoder2PinB 3

unsigned long currentMillis;
unsigned long previousArmMillis;
unsigned long previousMillis;

volatile long encoder0Pos = 0;    // encoder 1
volatile long encoder1Pos = 0;    // encoder 2
volatile long encoder2Pos = 0;    // encoder 3


void setup() {
  Serial.begin(9600);
  pinMode(encoder0PinA, INPUT_PULLUP);    // encoder pins
  pinMode(encoder0PinB, INPUT_PULLUP);

  pinMode(encoder1PinA, INPUT_PULLUP); 
  pinMode(encoder1PinB, INPUT_PULLUP);

  pinMode(encoder2PinA, INPUT_PULLUP);
  pinMode(encoder2PinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder0PinB), doEncoderB, CHANGE); 

  attachInterrupt(digitalPinToInterrupt(encoder1PinA), doEncoderC, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder1PinB), doEncoderD, CHANGE); 

  attachInterrupt(digitalPinToInterrupt(encoder2PinA), doEncoderE, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder2PinB), doEncoderF, CHANGE);

}


void loop() {
  currentMillis = millis();   // bookmark the time 
  if (currentMillis - previousMillis >= 10) {  // start timed loop for everything else
         previousMillis = currentMillis;
         Serial.print(encoder0Pos);
         Serial.print(",");
         Serial.print(encoder1Pos);
         Serial.print(",");
         Serial.println(encoder2Pos);
  }

}

// ************** encoders interrupts **************

// ************** encoder 1 *********************


void doEncoderA(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinB) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
 
}

void doEncoderB(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinA) == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  

}

// ************** encoder 2 *********************

void doEncoderC(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder1PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder1PinB) == LOW) {  
      encoder1Pos = encoder1Pos - 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder1PinB) == HIGH) {   
      encoder1Pos = encoder1Pos - 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;          // CCW
    }
  }
 
}

void doEncoderD(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder1PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder1PinA) == HIGH) {  
      encoder1Pos = encoder1Pos - 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder1PinA) == LOW) {   
      encoder1Pos = encoder1Pos - 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;          // CCW
    }
  }

}

// ************** encoder 3 *********************

void doEncoderE(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder2PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder2PinB) == LOW) {  
      encoder2Pos = encoder2Pos - 1;         // CW
    } 
    else {
      encoder2Pos = encoder2Pos + 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder2PinB) == HIGH) {   
      encoder2Pos = encoder2Pos - 1;          // CW
    } 
    else {
      encoder2Pos = encoder2Pos + 1;          // CCW
    }
  }
 
}

void doEncoderF(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder2PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder2PinA) == HIGH) {  
      encoder2Pos = encoder2Pos - 1;         // CW
    } 
    else {
      encoder2Pos = encoder2Pos + 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder2PinA) == LOW) {   
      encoder2Pos = encoder2Pos - 1;          // CW
    } 
    else {
      encoder2Pos = encoder2Pos + 1;          // CCW
    }
  }

}