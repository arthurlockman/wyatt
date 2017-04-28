//
// Created by Tucker Haydon on 4/27/17.
//

#include "../../include/commands/DriveMotorRPM.h"
#include <iostream>
#include <unistd.h>

DriveMotorRPM::DriveMotorRPM(Communicator* comm, Hardware motorHardware, EncoderSensor* encoder, int desiredRPM, int direction) : Command() {
    this->comm = comm;
    this->motorHardware = motorHardware;
    this->encoder = encoder;
    this->direction = direction;
    this->desiredRPM = desiredRPM;
    this->setpoint = 0.0;
}

DriveMotorRPM::~DriveMotorRPM() {
    // Nothing
}

bool DriveMotorRPM::execute() {

    double currentRPM = encoder->getRPM();
    std::cout << "Encoder: " << currentRPM << std::endl;

    double diff = this->desiredRPM - currentRPM;

    double pd = this->k_p * diff + this->k_d * (diff - lastDiff);
    this->setpoint = this->setpoint + pd;

    // Ensure that the control input is bounded
    if(fabs(this->setpoint) > FULL_FORWARD) {
        this->setpoint = FULL_FORWARD;
    }

    // Multiply by direction (1 or -1) because encoder only read abs(speed).
    this->setpoint *= this->direction;

    // Compose the motor message
    IMessage* msg = new MotorMessage(this->motorHardware, (int)(this->setpoint));

    // Send the message to the communicator
    comm->queueMessage(msg);
    usleep(100000);

    // Log the lastDiff
    this->lastDiff = diff;

    // Keep the PID running until this command is cancelled.
    return true;
}

bool DriveMotorRPM::cleanup(bool canceled) {
    return true;
}
