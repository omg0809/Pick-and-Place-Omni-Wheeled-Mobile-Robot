#include <Wire.h>
#include <L3G4200D.h>

L3G4200D gyroscope;

unsigned long timer = 0;
float timeStep = 0.01;

float yaw = 0;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize L3G4200D");

  while(!gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_400HZ_50))
  {
    Serial.println("Could not find a valid L3G4200D sensor, check wiring!");
    delay(500);
  }

  gyroscope.calibrate(100);

  //gyroscope.setThreshold(3);
}

void loop(){
  yawp();
}

void yawp(){
  timer = millis();

  Vector norm = gyroscope.readNormalize();

  yaw = yaw + norm.ZAxis * timeStep;
 
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  delay((timeStep*1000) - (millis() - timer));
}
