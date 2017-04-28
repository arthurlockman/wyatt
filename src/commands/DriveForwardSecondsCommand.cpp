#include "commands/DriveForwardSecondsCommand.h"
#include "time.h"
#include "DriveConstants.h"
#include <string>

DriveForwardSecondsCommand::DriveForwardSecondsCommand(DrivetrainAdapter *chassis, double seconds) :
    m_chassis(chassis),
    m_seconds(seconds),
    Command()
{
    m_startTime = time(0);

    MotorMessage* rightMessage = new MotorMessage(H_RIGHT_MOTOR, FULL_FORWARD);
    MotorMessage* leftMessage = new MotorMessage(H_LEFT_MOTOR, FULL_FORWARD);

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

    MotorMessage* rightMessage = new MotorMessage(H_RIGHT_MOTOR, FULL_STOP);
    MotorMessage* leftMessage = new MotorMessage(H_LEFT_MOTOR, FULL_STOP);

    m_chassis->write(rightMessage);
    m_chassis->write(leftMessage);
    return true;
}
