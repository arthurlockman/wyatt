#include "Main.h"

const Motor* leftMotor = new Motor(PWM_PIN_3, PWM_PIN_5);
const Motor* rightMotor = new Motor(PWM_PIN_6, PWM_PIN_9);
const IRSensor* irSensor = new IRSensor(IR_PIN);

void setup() {
  
  /* Initialize Serial */
  Serial.begin(9600);
}

void loop() {
    while(Serial.available()){
      unsigned char packetType = Serial.read();
              
      /* Determine the length of the incoming packet */
      unsigned char packetLength = HARDWARE_MAP[packetType].messageLength;
      
      /* Create a array to store the incoming message */
      unsigned char packet[packetLength];
     
      /* Receive the rest of the packet */
      for(int i = 0; i < packetLength; i++) {
        while(!Serial.available());
        packet[i] = Serial.read();
      }

      switch(packetType) {
        case LEFT_MOTOR_ADDRESS:
          driveMotor(leftMotor, packet[0]);
        break;
        case RIGHT_MOTOR_ADDRESS:
          driveMotor(rightMotor, packet[0]);
        break;
        default:
        break;
      }
    }
}

void driveMotor(Motor* motor, unsigned char motorSpeed) {

  int motorDirection;

  if(motorSpeed <= 127) {
    motorDirection = BACKWARDS;
    motorSpeed = map(motorSpeed, 127, 0, 0, 255);
  } else {
    motorDirection = FORWARDS;
    motorSpeed = map(motorSpeed, 128, 255, 0, 255);
  }

  motor->drive(motorSpeed, motorDirection);
}
