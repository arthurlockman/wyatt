#include "Main.h"

int main (void)
{

    /* Create sensor manager */
    ISensorManager* sensorManager = new SensorManager();

    /* Create a hardware peripheral */
    /* THIS CAUSES SEGFAULT BECAUSE OF NULL */
    IHardwareInterface* hardwareInterface = NULL;

    /* Create communicator and attach serial port */
    Communicator* comm = new Communicator(sensorManager, hardwareInterface);

    /* Start the thread */
    comm->start();

    /* Create test command */
    unsigned char commands[] = {H_LEFT_MOTOR.address, 0};
    Message* msg1 = new Message(H_LEFT_MOTOR, commands);

    /* Queue and send command */
    comm->queueMessage(msg1);

    comm->join();

    return 0 ;
}
