//
// Created by Arthur Lockman on 4/5/17.
//

#include "CommandManager.h"

CommandManager::CommandManager()
{
    std::cout << "Initialized command manager. Starting..." << std::endl;
    this->start();
}

CommandManager::~CommandManager()
{

}

bool CommandManager::runCommand(Command *command)
{
    mtx.lock();
    m_commands.push_back(command);
    m_command_flags.insert({command, 0});
    mtx.unlock();
    return true;
}

bool CommandManager::cancel(Command *command)
{
    mtx.lock();
    m_command_flags[command] = -1;
    mtx.unlock();
    return true;
}

bool CommandManager::cancelAll()
{
    mtx.lock();
    for (auto &command : m_commands) {
        m_command_flags[command] = -1;
    }
    mtx.unlock();
    return true;
}

void* CommandManager::run()
{
    while (m_signal == 0) {
        mtx.lock();
        for (auto &command : m_commands) {
            int flag = m_command_flags[command];
            if (!command->isFinished()) {
                if (!command->isInitialized()) {
                    command->init();
                    command->setIsRunning(true);
                } else if (flag == -1) // Cancel
                {
                    command->cancel();
                    m_command_flags[command] = 0;
                } else if (command->isRunning()) {
                    command->setIsRunning(command->execute());
                } else {
                    command->stop();
                }
            }
        }
        m_commands.remove_if([](Command* c){ return c->isFinished(); });
        mtx.unlock();
    }
    std::cout << "Received stop signal." << std::endl;
    return NULL;
}

int CommandManager::join()
{
    std::cout << "Stopping command manager." << std::endl;
    m_signal = 1;
    return Thread::join();
}

int CommandManager::kill()
{
    return this->join();
}

unsigned long CommandManager::inFlight()
{
    mtx.lock();
    unsigned long sz = m_commands.size();
    mtx.unlock();
    return sz;
}
