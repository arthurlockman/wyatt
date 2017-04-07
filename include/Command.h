#ifndef WYATT_COMMAND_H
#define WYATT_COMMAND_H

#include <string>

class Command {
public:
    /**
     * Create a new command.
     * @param name The command name.
     */
    Command(const std::string& name);
    /**
     * Destroy the command object.
     */
    virtual ~Command();

    /**
     * Initialize the command.
     */
    void init();
    /**
     * This method is called periodically during the
     * command execution. Think of it like the Arduino's
     * loop() function. While the command is executing
     * this will be called repeatedly. Do not include
     * while loops in here.
     * @return true if the command is done, false if it needs
     * to continue.
     */
    virtual bool execute() = 0;
    /**
     * This method is called when a command is canceled.
     * Cancellation only comes from the command manager,
     * so this method should never be directly called. You
     * do not necessarily need to override this function
     * in your command - it will call stop() by default.
     * Only override this if you need custom behavior for
     * when the command is stopped prematurely.
     */
    void cancel();
    /**
     * This method is called when a command has completed
     * execution. Use this method to clean up anything that the
     * command needs to clean before it is destroyed.
     */
    void stop();
    /**
     * Get if the command is running or not.
     * @return true if running, false otherwise.
     */
    bool isRunning();
    /**
     * Get if the command is initialized.
     * @return true if init() has been run, false otherwise.
     */
    bool isInitialized();
    /**
     * Get the name of the command.
     * @return A string, the command name.
     */
    std::string getName();
    /**
     * Set the running state of this command.
     * @param value bool, running or not
     */
    void setIsRunning(bool value);
private:
    //! The name of this command.
    std::string m_command_name;
    //! The running state of this command.
    bool m_is_running = false;
    //! The initialization state of this command.
    bool m_is_initialized = false;
};


#endif //WYATT_COMMAND_H
