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

    Chassis* chassis = new Chassis();

    std::string rightMessageString;
    rightMessageString.append(1, H_RIGHT_MOTOR.address);
    rightMessageString.append(1, 0b00000000);
    std::cout << (int)rightMessageString.at(1) << std::endl;

    std::string leftMessageString;
    leftMessageString.append(1, H_LEFT_MOTOR.address);
    leftMessageString.append(1, 0b00000000);
    std::cout << (int)leftMessageString.at(1) << std::endl;

    Message* rightMessage = new Message(H_RIGHT_MOTOR, rightMessageString);
    Message* leftMessage = new Message(H_LEFT_MOTOR, leftMessageString);

    chassis->write(rightMessage);
    chassis->write(leftMessage);

    return 0 ;
}
