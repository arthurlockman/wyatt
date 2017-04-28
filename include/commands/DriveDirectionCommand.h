#pragma once

#include "Command.h"
#include "hardwareinterface/DrivetrainAdapter.h"
#include <mutex>

class DriveDirectionCommand : public Command
{
public:
    DriveDirectionCommand(DrivetrainAdapter* chassis, int direction);
    ~DriveDirectionCommand();
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
    DrivetrainAdapter* m_chassis;
};
