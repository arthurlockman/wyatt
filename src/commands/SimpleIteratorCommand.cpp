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
    m_counter++;
    return m_counter != m_goal;
}

int SimpleIteratorCommand::getCount()
{
    return m_counter;
}
