#include "Main.h"

using namespace std;
int main (void)
{
    // wiringPiSetup () ;
    // pinMode (0, OUTPUT) ;
    // for (;;)
    // {
    //   digitalWrite (0, HIGH) ; delay (500) ;
    //   digitalWrite (0,  LOW) ; delay (500) ;
    // }

    /* Mocking out and Testing an IR Sensor */
    IRangeFinderSensor* mockIRSensor = new MockIRRangeFinderSensor();
    RawSensorData* mockRawSensorData = new RawSensorData("12.2");
    mockIRSensor->updateSensor(mockRawSensorData);
    cout << mockIRSensor->getDistanceCM() << endl;
    cout << mockIRSensor->getDistanceMM() << endl;

    /* Creating a sensor manager and testing it */
    list<ISensor*>* sensors = new list<ISensor*>;
    sensors->push_back(mockIRSensor);
    ISensorManager* sensorManager = new SensorManager(sensors);
    sensorManager->updateSensors();

    /* Creating a communicator and testing it */
    Communicator* comm = new Communicator(sensorManager);

    Message* msg1 = new Message(rightMotor, "test1");
    Message* msg2 = new Message(leftMotor, "test2");

    comm->queueMsg(msg1);
    comm->queueMsg(msg2);

    comm->sendNextMsg();
    comm->sendNextMsg();

    return 0 ;
}
