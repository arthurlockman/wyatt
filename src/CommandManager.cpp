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
    m_command_flags.at(command) = -1;
    mtx.unlock();
    return true;
}

bool CommandManager::cancelAll()
{
    mtx.lock();
    for (auto &command : m_commands) {
        this->cancel(command);
    }
    mtx.unlock();
    return true;
}

void* CommandManager::run()
{
    while (m_signal == 0) {
        mtx.lock();
        for (auto &command : m_commands) {
            int flag = m_command_flags.at(command);
            if (!command->isInitialized()) {
                command->init();
                command->setIsRunning(true);
            } else if (flag == -1) // Cancel
            {
                command->cancel();
            } else if (command->isRunning()) {
                command->setIsRunning(command->execute());
            } else {
                command->stop();
            }
        }
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
