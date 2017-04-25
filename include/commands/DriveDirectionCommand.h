#pragma once

#include "Command.h"
#include "Chassis.h"
#include <mutex>

class DriveDirectionCommand : public Command
{
public:
    DriveDirectionCommand(Chassis* chassis, int direction);
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
    Chassis* m_chassis;
};
