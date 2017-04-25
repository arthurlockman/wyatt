#include "commands/DriveDirectionCommand.h"
#include "DriveConstants.h"

DriveDirectionCommand::DriveDirectionCommand(Chassis *chassis, int direction) :
    m_chassis(chassis),
    Command()
{
    unsigned char rightDir;
    unsigned char leftDir;
    switch(direction) {
        case DriveDirectionCommand::DriveDirections::forward:
            rightDir = FULL_FORWARD;
            leftDir = FULL_FORWARD;
            break;
        case DriveDirectionCommand::DriveDirections::backward:
            rightDir = FULL_BACKWARD;
            leftDir = FULL_BACKWARD;
            break;
        case DriveDirectionCommand::DriveDirections::turnLeft:
            rightDir = FULL_FORWARD;
            leftDir = FULL_BACKWARD;
            break;
        case DriveDirectionCommand::DriveDirections::turnRight:
            rightDir = FULL_BACKWARD;
            leftDir = FULL_FORWARD;
            break;
        case DriveDirectionCommand::DriveDirections::stop:
        default:
            rightDir = FULL_STOP;
            leftDir = FULL_STOP;
            break;
    }
    std::string rightMessageString;
    rightMessageString.append(1, rightDir);
    Message* rightMessage = new Message(H_RIGHT_MOTOR, rightMessageString);

    std::string leftMessageString;
    leftMessageString.append(1, leftDir);
    Message* leftMessage = new Message(H_LEFT_MOTOR, leftMessageString);

    m_chassis->write(rightMessage);
    m_chassis->write(leftMessage);
}

DriveDirectionCommand::~DriveDirectionCommand()
{

}

bool DriveDirectionCommand::execute()
{
    return true;
}

bool DriveDirectionCommand::cleanup(bool canceled)
{
    return true;
}
