//
// Created by Tucker Haydon on 4/25/17.
//

#include "../include/Robot.h"


Robot::Robot() {

    /* Start wiring pi */
    wiringPiSetup();

    /* Create AdafruitPWMServo controller */
    this->pwmServoHat = new AdafruitPWMServoHat();

    /* Create hardware adapters */
    this->leftMotorAdapter =    new MotorAdapter(pwmServoHat, LEFT_MOTOR_FORWARD_PIN, LEFT_MOTOR_BACKWARD_PIN);
    this->rightMotorAdapter =   new MotorAdapter(pwmServoHat, RIGHT_MOTOR_FORWARD_PIN, RIGHT_MOTOR_BACKWARD_PIN);
    this->leftEncoderAdapter =  new EncoderAdapter(LEFT_ENCODER_PIN_A, LEFT_ENCODER_PIN_B, ENCODER_TICKS_PER_REVOLUTION, H_LEFT_ENCODER);
    this->rightEncoderAdapter = new EncoderAdapter(RIGHT_ENCODER_PIN_A, RIGHT_ENCODER_PIN_B, ENCODER_TICKS_PER_REVOLUTION, H_RIGHT_ENCODER);

    /* Create the sensors */
    this->leftEncoderSensor = new EncoderSensor();
    this->rightEncoderSensor = new EncoderSensor();

    /* Create the sensor manager and communicator */
    this->sensorManager = new SensorManager();
    this->communicator = new Communicator(sensorManager);

    /* Register the hardware adapters with the communicator */
    this->communicator->registerHardware(H_LEFT_MOTOR, this->leftMotorAdapter);
    this->communicator->registerHardware(H_RIGHT_MOTOR, this->rightMotorAdapter);
    this->communicator->registerHardware(H_LEFT_ENCODER, this->leftEncoderAdapter);
    this->communicator->registerHardware(H_RIGHT_ENCODER, this->rightEncoderAdapter);

    /* Register the sensors with the sensor manager */
    sensorManager->addSensor(H_LEFT_ENCODER, this->leftEncoderSensor);
    sensorManager->addSensor(H_RIGHT_ENCODER, this->rightEncoderSensor);

    /* Start the hardware adapters */
    this->rightEncoderAdapter->start();
    this->leftEncoderAdapter->start();

    /* Start the communicator */
    this->communicator->start();

}

Robot::~Robot() {

}