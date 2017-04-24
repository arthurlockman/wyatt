//
// Created by Arthur Lockman on 4/7/17.
//

#include "commands/SimpleIteratorCommand.h"

SimpleIteratorCommand::SimpleIteratorCommand(int goal):
    m_counter(0),
    m_goal(goal),
    Command()
{

}

SimpleIteratorCommand::~SimpleIteratorCommand()
{

}

bool SimpleIteratorCommand::execute()
{
    m_lock.lock();
    m_counter++;
    m_lock.unlock();
    return m_counter != m_goal;
}

int SimpleIteratorCommand::getCount()
{
    m_lock.lock();
    int count = m_counter;
    m_lock.unlock();
    return count;
}

bool SimpleIteratorCommand::cleanup(bool canceled)
{
    return true;
}
