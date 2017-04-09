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
    m_lock.lock();
    m_is_initialized = true;
    m_lock.unlock();
}

void Command::cancel()
{
    this->stop();
}

void Command::stop()
{
    m_lock.lock();
    m_is_running = false;
    m_is_finished = true;
    m_lock.unlock();
}

bool Command::isRunning()
{
    m_lock.lock();
    bool tmp = m_is_running;
    m_lock.unlock();
    return tmp;
}

bool Command::isInitialized()
{
    m_lock.lock();
    bool tmp = m_is_initialized;
    m_lock.unlock();
    return tmp;
}

void Command::setIsRunning(bool value)
{
    m_lock.lock();
    m_is_running = value;
    m_lock.unlock();
}

bool Command::isFinished()
{
    m_lock.lock();
    bool tmp = m_is_finished;
    m_lock.unlock();
    return tmp;
}
