#include "Main.h"

int main (void)
{
    // wiringPiSetup () ;
    // pinMode (0, OUTPUT) ;
    // for (;;)
    // {
    //   digitalWrite (0, HIGH) ; delay (500) ;
    //   digitalWrite (0,  LOW) ; delay (500) ;
    // }

    Message* msg1 = new Message(rightMotor, "test1");
    Message* msg2 = new Message(leftMotor, "test2");

    ISensorManager* fakeManager = NULL;

    Communicator* comm = new Communicator(fakeManager);

    comm->queueMsg(msg1);
    comm->queueMsg(msg2);

    comm->sendNextMsg();
    comm->sendNextMsg();

    ISensor* IRSensor = new IRRangeFinderSensor();
    IRSensor->updateSensor();

    return 0 ;
}
