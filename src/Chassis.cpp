//
// Created by Tucker Haydon on 4/23/17.
//

#include "../include/Chassis.h"

Chassis::Chassis() {
    this->m_pwmHat = new AdafruitPWMServoHat();
}

Chassis::~Chassis() {

}

void Chassis::write(Message* msg) {

    Hardware hardware = msg->getHardware();
    int messageLength = hardware.messageLength;
    int data[messageLength];

    for(int i = 1; i < messageLength; i++) {
        data[i] = msg->getMessage().at(i);
    }
    std::cout << (int)msg->getMessage().at(0) << std::endl;
    std::cout << (int)msg->getMessage().at(1) << std::endl;

    std::cout << data[0] << std::endl;
    if(hardware == H_RIGHT_MOTOR) {
        driveMotor(m_motor::RIGHT_MOTOR, data[0]);
    } else if(hardware == H_LEFT_MOTOR) {
        driveMotor(m_motor::LEFT_MOTOR, data[0]);
    } else {
        // TODO
        std::cout << "Error: No hardware found." << std::endl;
    }
}

void Chassis::driveMotor(m_motor motor, int speed) {

    int motorSpeed = mapMotorSpeed(speed);

    if(motor == m_motor::LEFT_MOTOR) {
        if(motorSpeed < 0) {
            m_pwmHat->setMotor(m_motorAddresses::left1, abs(motorSpeed));
            m_pwmHat->setMotor(m_motorAddresses::left2, 0);
        } else {
            m_pwmHat->setMotor(m_motorAddresses::left1, 0);
            m_pwmHat->setMotor(m_motorAddresses::left2, abs(motorSpeed));
        }

    } else if(motor == m_motor::RIGHT_MOTOR) {
        if(motorSpeed < 0) {
            m_pwmHat->setMotor(m_motorAddresses::right1, abs(motorSpeed));
            m_pwmHat->setMotor(m_motorAddresses::right2, 0);
        } else {
            m_pwmHat->setMotor(m_motorAddresses::right1, 0);
            m_pwmHat->setMotor(m_motorAddresses::right2, abs(motorSpeed));
        }
    }
}

int Chassis::mapMotorSpeed(int speed) {
    double mappedSpeed = (2 * 4096.0 * ((double)speed)/ 255.0 - 4096.0);
    return (int)mappedSpeed;
}

std::list<Message*>* Chassis::read() {
    return new std::list<Message*>;
}
