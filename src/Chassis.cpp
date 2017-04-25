//
// Created by Tucker Haydon on 4/23/17.
//

#include "../include/Chassis.h"

Chassis::Chassis() {
    this->m_pwmHat = new AdafruitPWMServoHat();
    this->m_rightEncoderCounter = new EncoderCounter(3, 4, 64, H_RIGHT_ENCODER);
    this->m_leftEncoderCounter = new EncoderCounter(1, 2, 64, H_LEFT_ENCODER);
}

Chassis::~Chassis() {
    delete this->m_pwmHat;
    delete this->m_rightEncoderCounter;
    delete this->m_leftEncoderCounter;
}

void Chassis::write(Message* msg) {

    Hardware hardware = msg->getHardware();
    int messageLength = hardware.messageLength;
    unsigned char data[messageLength];

    for(int i = 0; i < messageLength; i++) {
        data[i] = (unsigned char)msg->getMessage().at(i);
    }

    switch(hardware.address) {
        case RIGHT_MOTOR_ADDRESS:
            driveMotor(RIGHT_MOTOR_ADDRESS, data[0]);
            break;
        case LEFT_MOTOR_ADDRESS:
            driveMotor(LEFT_MOTOR_ADDRESS, data[0]);
            break;
        default:
            throw NonexistentHardwareException(hardware);
    }

    delete msg;
}

void Chassis::driveMotor(unsigned char motorAddress, unsigned char speed) {

    int motorSpeed = mapMotorSpeed(speed);
    switch(motorAddress) {
        case LEFT_MOTOR_ADDRESS:
            if(motorSpeed < 0) {
                m_pwmHat->setMotor(m_motorAddresses::left1, abs(motorSpeed));
                m_pwmHat->setMotor(m_motorAddresses::left2, 0);
            } else {
                m_pwmHat->setMotor(m_motorAddresses::left1, 0);
                m_pwmHat->setMotor(m_motorAddresses::left2, abs(motorSpeed));
            }
            break;
        case RIGHT_MOTOR_ADDRESS:
            if(motorSpeed < 0) {
                m_pwmHat->setMotor(m_motorAddresses::right1, abs(motorSpeed));
                m_pwmHat->setMotor(m_motorAddresses::right2, 0);
            } else {
                m_pwmHat->setMotor(m_motorAddresses::right1, 0);
                m_pwmHat->setMotor(m_motorAddresses::right2, abs(motorSpeed));
            }
            break;
    }
}

int Chassis::mapMotorSpeed(unsigned char speed) {
    double mappedSpeed = (2 * 4096.0 * ((double)speed)/ 255.0 - 4096.0);
    return (int)mappedSpeed;
}

std::list<Message*>* Chassis::read() {
    std::list<Message*>* messages = new std::list<Message*>;

    std::list<Message*>* rightEncoderMessages = m_rightEncoderCounter->read();
    std::list<Message*>* leftEncoderMessages = m_leftEncoderCounter->read();

    // Add all of the right messages to the message queue
    while (!rightEncoderMessages->empty())
    {
        Message* msg = rightEncoderMessages->front();
        messages->push_back(msg);
        rightEncoderMessages->pop_front();
    } 

    // Add all of the left messages to the message queue
    while (!leftEncoderMessages->empty())
    {
        Message* msg = leftEncoderMessages->front();
        messages->push_back(msg);
        leftEncoderMessages->pop_front();
    } 

    delete rightEncoderMessages;
    delete leftEncoderMessages;

    return messages;
}
