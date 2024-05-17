#include<Wire.h>

// Set MPU Address
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

// Ranges of Accelerometer Reading
int minVal=265;
int maxVal=402;

// Output Angles (degree)
double x;
double y;
double z;
 
void setup(){
  // Initialize MPU
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(38400);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);

  // Reading of Accelerometer
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();

  // Getting Angles using Accelerometer
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  
  // Output Angles in degree
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  
  // Printing Results
  Serial.print("AngleX= ");
  Serial.println(x);
  
  Serial.print("AngleY= ");
  Serial.println(y);

  Serial.print("ACY ");
  Serial.println(AcY);

  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("-----------------------------------------");
  delay(400);
}