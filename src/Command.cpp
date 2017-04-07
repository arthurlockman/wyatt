//
// Created by Arthur Lockman on 4/5/17.
//

#include "Command.h"

Command::Command(const std::string& name):
        m_command_name(name)
{

}

Command::~Command() {

}

void Command::init()
{
    m_is_initialized = true;
}

void Command::cancel()
{
    this->stop();
}

void Command::stop()
{
    m_is_running = false;
}

bool Command::isRunning()
{
    return m_is_running;
}

bool Command::isInitialized()
{
    return m_is_initialized;
}

std::string Command::getName()
{
    return m_command_name;
}

void Command::setIsRunning(bool value)
{
    m_is_running = value;
}
