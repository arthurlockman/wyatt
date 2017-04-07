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
    (*sensorMap)[H_MOCK_IR_SENSOR] = mockIRSensor;

    list<Message*>* updates = new list<Message*>;
    Message* updateIRMessage = new Message(H_MOCK_IR_SENSOR, "1.5");
    updates->push_back(updateIRMessage);

    ISensorManager* sensorManager = new SensorManager(sensorMap);
    sensorManager->updateSensors(updates);
    cout << "Expect: 1.5    Received: " << mockIRSensor->getDistanceCM() << endl;
    cout << "Expect: 15     Received: " << mockIRSensor->getDistanceMM() << endl;

    /* Creating a communicator and testing it */
    Communicator* comm = new Communicator(sensorManager);

    Message* msg1 = new Message(H_RIGHT_MOTOR, "test1");
    Message* msg2 = new Message(H_LEFT_MOTOR, "test2");

    
    comm->attachArduino("fake_comm_port_1", H_LEFT_MOTOR);
    comm->attachArduino("fake_comm_port_2", H_RIGHT_MOTOR);

    comm->queueMsg(msg1);
    comm->queueMsg(msg2);

    comm->sendNextMsg(H_LEFT_MOTOR);
    comm->sendNextMsg(H_RIGHT_MOTOR);

    cout << (int)H_RIGHT_MOTOR.address << endl;
    cout << (int)H_LEFT_MOTOR.messageLength << endl;

    cout << (int)HARDWARE_MAP[1].messageLength << endl;

    return 0 ;
}
