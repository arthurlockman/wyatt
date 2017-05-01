//
// Created by Arthur Lockman on 4/7/17.
//
#pragma once

#include "../../../include/commands/Command.h"
#include <mutex>
#include <atomic>

class SimpleIteratorCommand: public Command {
public:
    SimpleIteratorCommand(int goal);
    ~SimpleIteratorCommand();
    bool execute();
    bool cleanup(bool canceled);
    int getCount();
private:
    std::atomic<int> m_counter;
    int m_goal;
};
