#include "commands/DriveForwardSecondsCommand.h"
#include "time.h"
#include <string>

DriveForwardSecondsCommand::DriveForwardSecondsCommand(Chassis *chassis, double seconds) :
    m_chassis(chassis),
    m_seconds(seconds),
    Command()
{
    m_startTime = time(0);
    std::string rightMessageString;
    rightMessageString.append(1, H_RIGHT_MOTOR.address);
    rightMessageString.append(1, 0b00000000);
    std::cout << (int)rightMessageString.at(1) << std::endl;

    std::string leftMessageString;
    leftMessageString.append(1, H_LEFT_MOTOR.address);
    leftMessageString.append(1, 0b00000000);
    std::cout << (int)leftMessageString.at(1) << std::endl;

    Message* rightMessage = new Message(H_RIGHT_MOTOR, rightMessageString);
    Message* leftMessage = new Message(H_LEFT_MOTOR, leftMessageString);
    chassis->write(rightMessage);
    chassis->write(leftMessage);
}

DriveForwardSecondsCommand::~DriveForwardSecondsCommand()
{

}

bool DriveForwardSecondsCommand::execute()
{
    return this->isFinished();
}

bool DriveForwardSecondsCommand::isFinished()
{
    return difftime(time(0), m_startTime) > m_seconds;
}
