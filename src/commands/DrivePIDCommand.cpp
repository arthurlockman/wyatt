//
// Created by Arthur Lockman on 4/26/17.
//

#include "commands/DrivePIDCommand.h"

DrivePIDCommand::DrivePIDCommand(DrivetrainAdapter* drivetrain, int direction, EncoderSensor* rightEncoder, EncoderSensor* leftEncoder):
    m_drivetrain(drivetrain),
    m_leftEncoder(leftEncoder),
    m_rightEncoder(rightEncoder)
{
    switch(direction) {
        case DrivePIDCommand::DriveDirections::forward:
            m_rightDir = FULL_FORWARD;
            m_leftDir = FULL_FORWARD;
            break;
        case DrivePIDCommand::DriveDirections::backward:
            m_rightDir = FULL_BACKWARD;
            m_leftDir = FULL_BACKWARD;
            break;
        case DrivePIDCommand::DriveDirections::turnLeft:
            m_rightDir = FULL_FORWARD;
            m_leftDir = FULL_BACKWARD;
            break;
        case DrivePIDCommand::DriveDirections::turnRight:
            m_rightDir = FULL_BACKWARD;
            m_leftDir = FULL_FORWARD;
            break;
        case DrivePIDCommand::DriveDirections::stop:
        default:
            m_rightDir = FULL_STOP;
            m_leftDir = FULL_STOP;
            break;
    }
}

DrivePIDCommand::~DrivePIDCommand()
{

}

bool DrivePIDCommand::execute()
{
    return false;
}

bool DrivePIDCommand::cleanup(bool canceled)
{
    return true;
}
