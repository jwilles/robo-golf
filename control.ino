#include<Servo.h>

//Defining Pins
const int ControlL1 = 6;
const int ControlL2 = 7;
const int ControlR1 = 12;
const int ControlR2 = 13;
const int DirectionPin = 3;
const int LMotorP = 4;
const int RMotorP = 5;
const int LMotorE = 9;
const int RMotorE = 10;
const int SpeedPot = A0;
const int ServoPot = A1;

//Servo Setup
Servo ArmServo;


//Variable Init 
int ServoPotVal;
int angle;

int lPowerSwitchState = 0;
int rPowerSwitchState = 0;
int directionSwitchState = 0;
int prevDirectionSwitchState = 0;

int motorSpeed = 0;
boolean motorDirection = false;


void setup(){
  
  //Defining Pin Modes
  pinMode(ControlL1, OUTPUT);
  pinMode(ControlL2, OUTPUT);
  pinMode(ControlR1, OUTPUT);
  pinMode(ControlR2, OUTPUT);
  pinMode(DirectionPin, INPUT);
  pinMode(LMotorP, INPUT);
  pinMode(RMotorP, INPUT);
  ArmServo.attach(11);
  pinMode(LMotorE, OUTPUT);
  pinMode(RMotorE, OUTPUT);
  
  //Setting Motor Enabling Off
  digitalWrite(LMotorE, LOW);
  digitalWrite(RMotorE, LOW);
  
  Serial.begin(9600);
  
}
  
void loop(){
  
  //Reading Sensors
  lPowerSwitchState = digitalRead(LMotorP);
  delay(1);
  rPowerSwitchState = digitalRead(RMotorP);
  delay(1);
  directionSwitchState = digitalRead(DirectionPin);
  
  motorSpeed = analogRead(SpeedPot)/4;
  
  
  ServoPotVal = analogRead(ServoPot);
  angle = map(ServoPotVal, 0, 1023, 0, 179);
  ArmServo.write(angle);
  delay(15);
   
   
   //Read direction switch
  if(directionSwitchState == HIGH 
      && directionSwitchState != prevDirectionSwitchState) {
    motorDirection = !motorDirection;
  }

  //Read power switch
  if(lPowerSwitchState == HIGH) {
    analogWrite(LMotorE, motorSpeed);
    Serial.println("LMotor on");
  }
  else{
      analogWrite(LMotorE, 0);
      Serial.println("LMotor off");
  }
  if(rPowerSwitchState == HIGH) {
    analogWrite(RMotorE, motorSpeed);
    Serial.println("RMotor on");
  }
  else{
      analogWrite(RMotorE, 0);
      Serial.println("RMotor off");
  }
  
  //Set H-bridge direction 
  if(motorDirection) {
    digitalWrite(ControlL1, HIGH);
    digitalWrite(ControlL2, LOW);
     digitalWrite(ControlR1, HIGH);
    digitalWrite(ControlR2, LOW);
  }
  else {
    digitalWrite(ControlL1, LOW);
    digitalWrite(ControlL2, HIGH);
     digitalWrite(ControlR1, LOW);
    digitalWrite(ControlR2, HIGH);
  }
  
 
  
  //Preserve state 
  prevDirectionSwitchState = directionSwitchState;
  
  
  
}
