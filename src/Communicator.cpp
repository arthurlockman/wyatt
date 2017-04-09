#include "Communicator.h"
using namespace std;

Communicator::~Communicator() {
    // TODO close serial lines
}

Communicator::Communicator(ISensorManager* sensorManager, int baudRate) {
    this->sensorManager = sensorManager;
    this->baudRate = baudRate;

    // Map for all hardware attachments to their communication port paths.
    this->hardwareToSerialPortPathMap = new map<Hardware, string>;  

    // Map hardware to serial port objects
    this->hardwareToSerialPortMap = new map<Hardware, SerialPort*>;

    // Map of Hardware attachments to their message queue. 
    this->hardwareToMessageQueueMap = new map<Hardware, queue<Message*>*>;
}

void Communicator::attachHardware(string comPort, Hardware hardwareTarget) {
	// Check if hardware key already exists within our map of hardware->communication port
    if (this->hardwareToSerialPortPathMap->find(hardwareTarget) != this->hardwareToSerialPortPathMap->end()) {
    	// You can't reattach this, and this comPort is already attached to a piece of hardware!
        throw new ArduinoMappingException();
    }
    else {
    	// Add the mapping from hardware target enum to the specified com port.
    	this->hardwareToSerialPortPathMap->insert(make_pair(hardwareTarget, comPort));

        // Create a SerialPort and open it
        SerialPort* port = new SerialPort(comPort.c_str(), this->baudRate);
        port->open();
        this->hardwareToSerialPortMap->insert(make_pair(hardwareTarget, port));

    	// When we attach hardware, we want to be able to enqueue messages to that piece of hardware.
    	// Thus, we have a mashmap that goes from Hardware to a queue associated with messages to that hardware.
    	queue<Message*>* msg_queue = new queue<Message*>;
    	this->hardwareToMessageQueueMap->insert(make_pair(hardwareTarget, msg_queue));
    }
}
 

void Communicator::sendNextMsg(Hardware hardwareTarget) {
    if(this->hardwareToMessageQueueMap->at(hardwareTarget)->empty()) {
        throw new EmptyMessageQueueException();
    }

    // Get pointer to start of message from queue
    Message* msg = this->hardwareToMessageQueueMap->at(hardwareTarget)->front();
    char* message = msg->getMessage();
    int messageLength = HARDWARE_MAP[hardwareTarget.address].messageLength + 1;

    // Send the message
    hardwareToSerialPortMap->at(hardwareTarget)->write(message, messageLength);

    // Remove the message from the queue
    this->hardwareToMessageQueueMap->at(hardwareTarget)->pop();
    delete msg;
}

void Communicator::readData() {
    // TODO
    return;
}

void Communicator::queueMessage(Message *msg) {
    //Attempt to enqueue the message. If we can't, then throw an error because there's not a queue for that message's associated hardware. 
    try {
        Hardware h = msg->getHardware();

        // Push message into queue specified by hardware
        this->hardwareToMessageQueueMap->at(msg->getHardware())->push(msg);
        return;
    }
    catch (const out_of_range oor_map) {
        throw new MessageHasNoQueueException();
    }
}

