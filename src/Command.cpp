//
// Created by Arthur Lockman on 4/5/17.
//

#include "Command.h"

Command::Command()
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
    m_is_finished = true;
}

bool Command::isRunning()
{
    return m_is_running;
}

bool Command::isInitialized()
{
    return m_is_initialized;
}

void Command::setIsRunning(bool value)
{
    m_is_running = value;
}

bool Command::isFinished()
{
    return m_is_finished;
}