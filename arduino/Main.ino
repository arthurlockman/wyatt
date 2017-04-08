#include "Main.h"

/* Define hardware components */
const Motor* leftMotor = new Motor(PWM_PIN_3, PWM_PIN_5);
const Motor* rightMotor = new Motor(PWM_PIN_6, PWM_PIN_9);
const IRSensor* irSensor = new IRSensor(IR_PIN);

void setup() {
  
  /* Initialize Serial */
  Serial.begin(9600);
}

void loop() {
  /* Poll sensors, etc */
}

/*
* Runs at the end of each loop and runs if there is new serial data.
*/
void serialEvent() {

  /* First byte indicates the packet type */
  unsigned char packetType = Serial.read();
              
  /* Check how many more bytes to read */
  unsigned char packetLength = HARDWARE_MAP[packetType].messageLength;
  
  /* Create a array to store the incoming bytes */
  unsigned char packet[packetLength];
 
  /* Receive the rest of the packet */
  for(int i = 0; i < packetLength; i++) {
    while(!Serial.available());
    packet[i] = Serial.read();
  }

  /* Dispatch the message based on packet type */
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

/*
* Drives a motor at a specified speed.
* motor - The motor to drive
* motorSpeed - The speed to drive the motor at, specified as a byte. 00: Full backwards, FF: Full forwards, 7f/80: Stop
*/
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
