#pragma once

#include "Command.h"
#include "hardwareinterface/DrivetrainAdapter.h"
#include <mutex>

class DriveForwardSecondsCommand : public Command
{
public:
    DriveForwardSecondsCommand(DrivetrainAdapter* chassis, double seconds);
    ~DriveForwardSecondsCommand();
    bool execute();
    bool cleanup(bool canceled);
private:
    DrivetrainAdapter* m_chassis;
    double m_seconds;
    time_t m_startTime;
};
