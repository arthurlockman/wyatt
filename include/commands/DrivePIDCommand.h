//
// Created by Arthur Lockman on 4/26/17.
//

#pragma once

#include "Command.h"
#include "sensors/EncoderSensor.h"
#include "hardwareinterface/DrivetrainAdapter.h"

class DrivePIDCommand: public Command
{
public:
    DrivePIDCommand(DrivetrainAdapter* drivetrain, int direction, EncoderSensor* rightEncoder, EncoderSensor* leftEncoder);
    ~DrivePIDCommand();
    bool execute();
    bool cleanup(bool canceled);
    enum DriveDirections {
        stop = 0,
        forward,
        backward,
        turnLeft,
        turnRight
    };
private:
    DrivetrainAdapter* m_drivetrain;
    EncoderSensor* m_rightEncoder;
    EncoderSensor* m_leftEncoder;
    double k_p = 1.0;
    double k_i = 1.0;
    double k_d = 1.0;
    int m_rightDir;
    int m_leftDir;
    void updatePID();
};

