#include "Main.h"

class MyThread : public Thread
{
    public:
    void *run() {
        for (int i = 0; i < 5; i++) {
            printf("thread %lu running - %d\n",  (long unsigned int)self(), i+1);
            sleep(2);
        }
        printf("thread done %lu\n", (long unsigned int)self());
        return NULL;
    }
};

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

    ISensorManager* fakeManager = new ISensorManager();

    Communicator* comm = new Communicator(fakeManager);

    comm->queueMsg(msg1);
    comm->queueMsg(msg2);

    comm->sendNextMsg();
    comm->sendNextMsg();

    MyThread* thread1 = new MyThread();
    MyThread* thread2 = new MyThread();
    thread1->start();
    thread2->start();
    thread1->join();
    thread2->join();
    printf("main done\n");

    return 0 ;
}
