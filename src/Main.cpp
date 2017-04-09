#include <commands/SimpleIteratorCommand.h>
#include "Main.h"

using namespace std;
int main (void)
{
    wiringPiSetup();

    /* Create sensor manager */
    ISensorManager* sensorManager = new SensorManager();

    /* Create communicator and attach serial port */
    Communicator* comm = new Communicator(sensorManager, 9600);
    comm->attachArduino("/dev/ttyUSB0", H_LEFT_MOTOR);

    /* Create test command */
    char commands[] = {0b00000001, 0b00000000};
    Message* msg1 = new Message(H_LEFT_MOTOR, commands);

    /* Queue and send command */
    comm->queueMsg(msg1);
    comm->sendNextMsg(H_LEFT_MOTOR);

    return 0 ;
}
