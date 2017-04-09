#include <commands/SimpleIteratorCommand.h>
#include "Main.h"

using namespace std;
int main (void)
{
    wiringPiSetup();

    // (*sensorMap)[H_MOCK_IR_SENSOR] = mockIRSensor;

    // list<Message*>* updates = new list<Message*>;
    // Message* updateIRMessage = new Message(H_MOCK_IR_SENSOR, "1.5");
    // updates->push_back(updateIRMessage);

    ISensorManager* sensorManager = new SensorManager();
    // sensorManager->updateSensors(updates);
    // cout << "Expect: 1.5    Received: " << mockIRSensor->getDistanceCM() << endl;
    // cout << "Expect: 15     Received: " << mockIRSensor->getDistanceMM() << endl;

    /* Creating a communicator and testing it */
    Communicator* comm = new Communicator(sensorManager, 9600);

    char commands[] = {0b00000001, 0b00000000};
    Message* msg1 = new Message(H_LEFT_MOTOR, commands);
    // Message* msg2 = new Message(H_LEFT_MOTOR, "test2");
    
    comm->attachArduino("/dev/ttyUSB0", H_LEFT_MOTOR);
    // comm->attachArduino("fake_comm_port_2", H_RIGHT_MOTOR);

    comm->queueMsg(msg1);
    // comm->queueMsg(msg2);

    comm->sendNextMsg(H_LEFT_MOTOR);
    cout << "End" << endl;
    // comm->sendNextMsg(H_RIGHT_MOTOR);

    // cout << (int)H_RIGHT_MOTOR.address << endl;
    // cout << (int)H_LEFT_MOTOR.messageLength << endl;

    // cout << (int)HARDWARE_MAP[1].messageLength << endl;

    // CommandManager *commandManager = new CommandManager();
    // commandManager->kill();

    return 0 ;
}
