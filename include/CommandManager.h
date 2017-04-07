//
// Created by Arthur Lockman on 4/5/17.
//

#ifndef WYATT_COMMANDMANAGER_H
#define WYATT_COMMANDMANAGER_H

#include "Command.h"
#include "Thread.h"
#include <vector>
#include <iostream>
#include <map>

class CommandManager: public Thread {
public:
    CommandManager();
    ~CommandManager();
    bool run(Command* command);
    bool cancel(Command* command);
    bool cancelAll();
    void* run();
    int join();
private:
    std::vector<Command*> m_commands;
    std::map<Command*, int> m_command_flags;
};

#endif //WYATT_COMMANDMANAGER_H
