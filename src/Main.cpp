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
    cout << "Expect: 12.2    Received: " << mockIRSensor->getDistanceCM() << endl;
    cout << "Expect: 122     Received: " << mockIRSensor->getDistanceMM() << endl;

    /* Creating a sensor manager and testing it */
    map<Hardware, ISensor*>* sensorMap = new map<Hardware, ISensor*>;
    (*sensorMap)[Hardware::mockIRSensor] = mockIRSensor;

    list<Message*>* updates = new list<Message*>;
    Message* updateIRMessage = new Message(Hardware::mockIRSensor, "1.5");
    updates->push_back(updateIRMessage);

    ISensorManager* sensorManager = new SensorManager(sensorMap);
    sensorManager->updateSensors(updates);
    cout << "Expect: 1.5    Received: " << mockIRSensor->getDistanceCM() << endl;
    cout << "Expect: 15     Received: " << mockIRSensor->getDistanceMM() << endl;

    /* Creating a communicator and testing it */
    Communicator* comm = new Communicator(sensorManager);

    Message* msg1 = new Message(Hardware::rightMotor, "test1");
    Message* msg2 = new Message(Hardware::leftMotor, "test2");

    
    comm->attachArduino("fake_comm_port_1", leftMotor);
    comm->attachArduino("fake_comm_port_2", rightMotor);

    comm->queueMsg(msg1);
    comm->queueMsg(msg2);

    comm->sendNextMsg(leftMotor);
    comm->sendNextMsg(rightMotor);

    CommandManager* commandManager = new CommandManager();
    commandManager->join();
    
    return 0 ;
}
