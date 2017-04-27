//
// Created by Tucker Haydon on 4/27/17.
//

#include "../../include/commands/DriveMotorRPM.h"

DriveMotorRPM::DriveMotorRPM(Communicator* comm, Hardware motorHardware, EncoderSensor* encoder, int desiredRPM, int direction) : Command() {
    this->comm = comm;
    this->motorHardware = motorHardware;
    this->encoder = encoder;
    this->direction = direction;
    this->desiredRPM = desiredRPM;
}

DriveMotorRPM::~DriveMotorRPM() {
    // Nothing
}

bool DriveMotorRPM::execute() {

    double currentRPM = encoder->getRPM();
    double diff = this->desiredRPM - currentRPM;

    double motorSpeed = this->k_p * diff + this->k_d * (diff - lastDiff);

    // Ensure that the control input is bounded
    if(fabs(motorSpeed) > FULL_FORWARD) {
        motorSpeed = FULL_FORWARD;
    }

    // Multiply by direction (1 or -1) because encoder only read abs(speed).
    motorSpeed *= this->direction;

    // Compose the motor message
    IMessage* msg = new MotorMessage(this->motorHardware, (int)motorSpeed);

    // Send the message to the communicator
    comm->queueMessage(msg);

    // Log the lastDiff
    this->lastDiff = diff;

    // Keep the PID running until this command is cancelled.
    return true;
}

bool DriveMotorRPM::cleanup(bool canceled) {
    return true;
}