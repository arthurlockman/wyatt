//
// Created by Tucker Haydon on 4/28/17.
//

#include "../../include/commands/DriveRobotCommand.h"

DriveRobotCommand::DriveRobotCommand(Communicator* comm, EncoderSensor* leftEncoder, EncoderSensor* rightEncoder, double radius, double rotationRate, int duration_ms, double wheelDiameter, double drivetrainDiameter) : Command() {

    this->duration_ms = duration_ms;

    double leftMotorRPM = - rotationRate * (radius + drivetrainDiameter/2) * 60.0 / (3.14159 * wheelDiameter);
    double rightMotorRPM = - rotationRate * (radius - drivetrainDiameter/2) * 60.0 / (3.14159 * wheelDiameter);
    int leftMotorDirection = leftMotorRPM < 0 ? BACKWARD_DIRECTION : FORWARD_DIRECTION;
    int rightMotorDirection = rightMotorRPM < 0 ? BACKWARD_DIRECTION : FORWARD_DIRECTION;

    this->leftMotorCommand = new DriveMotorRPM(comm, H_LEFT_MOTOR, leftEncoder, fabs(leftMotorRPM), leftMotorDirection);
    this->rightMotorCommand = new DriveMotorRPM(comm, H_RIGHT_MOTOR, rightEncoder, fabs(rightMotorRPM), rightMotorDirection);
}

DriveRobotCommand::~DriveRobotCommand() {
    // Nothing?
}

bool DriveRobotCommand::execute() {

    // Get the current time in ms
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long currentTime = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000;

    // If the first execution
    if(this->endTime == -1L) {
        this->endTime = currentTime + this->duration_ms;
    }

    // Drive the motors
    this->leftMotorCommand->execute();
    this->rightMotorCommand->execute();

    if(currentTime >= endTime) {
        // Does not need to continue
        return false;
    } else {
        // Needs to continue executing
        return true;
    }
}

bool DriveRobotCommand::cleanup(bool canceled) {
    this->leftMotorCommand->cancel();
    this->rightMotorCommand->cancel();

    return true;
}