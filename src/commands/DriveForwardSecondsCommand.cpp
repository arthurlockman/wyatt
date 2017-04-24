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
    rightMessageString.append(1, 0b10000000);
    Message* rightMessage = new Message(H_RIGHT_MOTOR, rightMessageString);

    std::string leftMessageString;
    leftMessageString.append(1, 0b11111111);
    Message* leftMessage = new Message(H_LEFT_MOTOR, leftMessageString);

    m_chassis->write(rightMessage);
    m_chassis->write(leftMessage);
}

DriveForwardSecondsCommand::~DriveForwardSecondsCommand()
{

}

bool DriveForwardSecondsCommand::execute()
{
    return difftime(time(0), m_startTime) < m_seconds;
}

bool DriveForwardSecondsCommand::cleanup(bool canceled)
{
    std::cout << "Ran for " << difftime(time(0), m_startTime) << " seconds." << std::endl;
    // TODO: Send message to stop motor.
    std::string rightMessageString;
    rightMessageString.append(1, H_RIGHT_MOTOR.address);
    rightMessageString.append(1, 0b00000000);

    std::string leftMessageString;
    leftMessageString.append(1, H_LEFT_MOTOR.address);
    leftMessageString.append(1, 0b00000000);

    Message* rightMessage = new Message(H_RIGHT_MOTOR, rightMessageString);
    Message* leftMessage = new Message(H_LEFT_MOTOR, leftMessageString);
    m_chassis->write(rightMessage);
    m_chassis->write(leftMessage);
    return true;
}
