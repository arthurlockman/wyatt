#pragma once

#include "Command.h"
#include "Chassis.h"
#include <mutex>

class DriveForwardSecondsCommand : public Command
{
public:
    DriveForwardSecondsCommand(Chassis* chassis, double seconds);
    ~DriveForwardSecondsCommand();
    bool execute();
    bool cleanup(bool canceled);
private:
    Chassis* m_chassis;
    double m_seconds;
    time_t m_startTime;
};
