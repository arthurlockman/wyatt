//
// Created by Arthur Lockman on 4/7/17.
//

#ifndef WYATT_SIMPLEITERATORCOMMAND_H
#define WYATT_SIMPLEITERATORCOMMAND_H

#include "Command.h"
#include <mutex>

class SimpleIteratorCommand: public Command {
public:
    SimpleIteratorCommand(int goal);
    ~SimpleIteratorCommand();
    bool execute();
    bool cleanup(bool canceled);
    int getCount();
private:
    int m_counter;
    int m_goal;
};

#endif //WYATT_SIMPLEITERATORCOMMAND_H
