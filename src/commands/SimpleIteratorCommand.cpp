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
    lck.lock();
    m_counter++;
    lck.unlock();
    return m_counter != m_goal;
}

int SimpleIteratorCommand::getCount()
{
    lck.lock();
    int count = m_counter;
    lck.unlock();
    return count;
}
