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

    
    comm->attachArduino("fake_comm_port_1", leftMotor);
    comm->attachArduino("fake_comm_port_2", rightMotor);

    comm->queueMsg(msg1);
    comm->queueMsg(msg2);

    comm->sendNextMsg(leftMotor);
    comm->sendNextMsg(rightMotor);

    /* Mocking out and Testing an IR Sensor */
    IRangeFinderSensor* mockIRSensor = new MockIRRangeFinderSensor();
    RawSensorData* mockRawSensorData = new RawSensorData("12.2");
    mockIRSensor->updateSensor(mockRawSensorData);
    cout << mockIRSensor->getDistanceCM() << endl;
    cout << mockIRSensor->getDistanceMM() << endl;

    return 0 ;
}
