#include "Main.h"

int main (void)
{

//    /* Create sensor manager */
//    ISensorManager* sensorManager = new SensorManager();
//
//    /* Create a hardware peripheral */
//    /* THIS CAUSES SEGFAULT BECAUSE OF NULL */
//    IHardwareInterface* hardwareInterface = NULL;
//
//    /* Create communicator and attach serial port */
//    Communicator* comm = new Communicator(sensorManager, hardwareInterface);
//
//    /* Start the thread */
//    comm->start();
//
//    /* Create test command */
//    std::string command = "";
//    command.append(1, H_LEFT_MOTOR.address);
//    command.append(1, (unsigned char)0);
//
//    Message* msg1 = new Message(H_LEFT_MOTOR, command);
//
//    /* Queue and send command */
//    comm->queueMessage(msg1);
//
//    comm->join();
   
    // Setup WiringPi 
    wiringPiSetup();
    
    // Create robot command manager
    CommandManager* m_commandManager = new CommandManager();

    // Create robot chassis object
    Chassis* m_chassis = new Chassis();

    // Temporary, testing drive
    DriveForwardSecondsCommand* tmp_driveCmd = new DriveForwardSecondsCommand(m_chassis, 5.0);
    m_commandManager->runCommand(tmp_driveCmd);

    // Wait for command to finish
    while (!tmp_driveCmd->isFinished()) {
        std::list<Message*>* chassisMessages = m_chassis->read();   

        while(!chassisMessages->empty()) {

            Message* msg = chassisMessages->front();
            if( (msg->getHardware()).address == LEFT_ENCODER_ADDRESS) {
                const char* charArray = (msg->getMessage()).c_str();
                double left = *((double*)charArray);
                std::cout << "Left: " << left << std::endl;
            }

            if( (msg->getHardware()).address == RIGHT_ENCODER_ADDRESS) {
                const char* charArray = (msg->getMessage()).c_str();
                double right = *((double*)charArray);
                std::cout << "Right: " << right << std::endl;
            }

            delete msg;
            chassisMessages->pop_front();
        }        
        delete chassisMessages;
    }

    //Kill command manager.
    m_commandManager->kill();

    return 0 ;
}
