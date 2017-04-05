#ifndef WYATT_COMMAND_H
#define WYATT_COMMAND_H

class Command: public Thread {
public:
    Command(const std::string& name);
    virtual ~Command();

    void init();
    void execute();
    void cancel();
    void stop();
    bool isRunning();
    bool isInitialized();
private:
    std::string m_command_name;
    volatile bool m_is_running = false;
    bool m_is_initialized = false;
};


#endif //WYATT_COMMAND_H
