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

    AdafruitPWMServoHat* controller = new AdafruitPWMServoHat();

    for(int i = 0; i < 4096; i++) {
    	controller->setMotor(0, i);
    	usleep(10000);
    }

    return 0 ;
}
