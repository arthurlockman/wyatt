#include "main.h"

int main (void)
{
    // wiringPiSetup () ;
    // pinMode (0, OUTPUT) ;
    // for (;;)
    // {
    //   digitalWrite (0, HIGH) ; delay (500) ;
    //   digitalWrite (0,  LOW) ; delay (500) ;
    // }

    Message* msg1 = new Message("test1");
    Message* msg2 = new Message("test2");

    ISensorManager* fakeManager = new ISensorManager();

    Communicator* comm = new Communicator(fakeManager);

    comm->queueMsg(msg1);
    comm->queueMsg(msg2);

    comm->sendNextMsg();
    comm->sendNextMsg();

    return 0 ;

}
