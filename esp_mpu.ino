#include <Adafruit_MPU6050.h>
#include <MPU6050.h>
#include <Wire.h>
#include<Adafruit_Sensor.h>


//mpu object if the Adafruit lbrary
Adafruit_MPU6050 mpu;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // Initial srial communication with the baudrate 115200
  if (!mpu.begin()) {                                // checking if the MPU6050 is detected .If not detected it enters a while loop Infinitely 
   Serial.println("Failed to find MPU6050 chip");  
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);      // set the range . there are (+2g , +4g , +8g ,+16g) 
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);  
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t a , g,temp;
  if(mpu.getEvent(&a,&g,&temp))
  {
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  }
  delay(1000);

 }
