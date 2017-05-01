//
// Created by Tucker Haydon on 4/28/17.
//

#pragma once
#include "Command.h"
#include "../../include/commands/DriveMotorRPM.h"
#include <sys/time.h>
#include <math.h>

class DriveRobotCommand:public Command {

public:
    /**
     * Constructor
     * @param comm Communicator
     * @param leftEncoder LeftEncoder object
     * @param rightEncoder RightEncoder object
     * @param radius Distance from center of robot to turning center in cm. Right = positive, left = negative
     * @param rotationRate The rate of rotation in rads/second
     * @param duration_ms The time in milliseconds to run this command for
     * @param wheelDiameter The diameter of the wheels in cm
     * @param drivetrainDiameter The distance between the wheels in cm
     */
    DriveRobotCommand(Communicator* comm, EncoderSensor* leftEncoder, EncoderSensor* rightEncoder, double radius, double rotationRate, int duration_ms, double wheelDiameter, double drivetrainDiameter);
    ~DriveRobotCommand();

    /**
    * Return true until time is expired
    * @return True.
    */
    bool execute() override;

    /**
     * Stop the respective motor commands. Will no longer perform PD control. Does not change the last motor write value.
     * @param canceled
     * @return True
     */
    bool cleanup(bool canceled) override;

private:
    int duration_ms;
    long long endTime = -1;
    Command* leftMotorCommand;
    Command* rightMotorCommand;


};
