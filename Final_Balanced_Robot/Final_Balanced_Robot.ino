#include<Wire.h>

// Set MPU Address
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

// Ranges of Accelerometer Reading
int minVal=265;
int maxVal=402;

// Desired Angle
int desired_angle = 91;

// Actual/Initial Angle
int actual_angle;

// Motor Variables
const int IN1 = 13;
const int IN2 = 12;
const int IN3 = 7;
const int IN4 = 8;
const int ENA = 11;
const int ENB = 6;

// PID Parameters/Gains/Variables
float kp = 3;
float ki = 0.3;
float kd = 2;
float error_accum = 0.0;
float error_previous = 0.0;
float previous_time = 0.0;

// PWM of motor speed
int pwm;

void setup() {
  // Initialize MPU
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(38400);
}

void loop() {

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);

  // Reading of Accelerometer
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();

  // Getting Angles using Accelerometer
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  // Getting Actual Angle in degree
  actual_angle= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);

  // Serial.print("AngleX= ");
  // Serial.println(actual_angle);

  // Serial.println("-----------------------------------------");
  // delay(400);


  // Calculate PID error and control signal
  float error = desired_angle - actual_angle;
  error_accum += error;
  float pid_output = kp * error + ki * error_accum + kd * (error - error_previous) / (millis() - previous_time);

  // Serial.print("pid= ");
  // Serial.println(pid_output);

  // Serial.println("-----------------------------------------");
  // delay(400);

  // Forward Motion
  if(pid_output > 0  and pid_output < 90){

    pwm = map(pid_output, 0, 90, 0, 150);

    forward(pwm);

    // Serial.print("pwm_forward= ");
    // Serial.println(pwm);

    // Serial.println("-----------------------------------------");
    // delay(400);
  }

  // Backward Motion 
  else if(pid_output < 0 and pid_output > -90){

    pwm = map(pid_output, abs(-90), 0, 100, 0);
    backward(pwm);
    
    // Serial.print("pwm_backward= ");
    // Serial.println(pwm);

    // Serial.println("-----------------------------------------");
    // delay(400);
  }

}

// Movement states
void backward(int pwm){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, pwm);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, pwm);
}

void forward(int pwm){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, pwm);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, pwm);
}

