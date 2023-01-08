#include<Wire.h>
#include<MPU6050.h>

MPU6050 mpu;

unsigned long timer = 0;
float timeStep = 0.01;

float pitch = 0;
float roll = 0;
float yaw = 0;

void setup(){
    Serial.begin(115200);

    while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
    {
        Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
        delay(500);
    }

    mpu.calibrateGyro();

    mpu.setThreshold(3);
}

void loop(){
    timer = millis();

    Vector norm = mpu.readNormalizeGyro();

    pitch = pitch + norm.YAxis * timeStep;
    roll = roll + norm.XAxis * timeStep;
    yaw = yaw + norm.YAxis * timeStep;

    Serial.print(" Pitch = ");
    Serial.print(pitch);
    Serial.print(" Roll = ");
    Serial.print(roll);
    Serial.print(" Yaw = ");
    Serial.print(yaw);
}
