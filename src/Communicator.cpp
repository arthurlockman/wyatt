#include "Communicator.h"

Communicator::Communicator(ISensorManager* sensorManager) {
    this->sensorManager = sensorManager;

    this->hardware_map = new map<Hardware, string>; // Map for all hardware attachments to their associated com port. 
    this->msg_queue_map = new map<Hardware, queue<Message*>*>; // Map of Hardware attachments to their message queues.
}

bool Communicator::attachArduino (string comPort, Hardware hardware_target) {

	// Check if key is present. If it is, fail.
    if (this->hardware_map->find(hardware_target) != this->hardware_map->end())
    {
    	// You can't reattach this, and this comPort is already attached to a piece of hardware!
    	// Are you attaching the same component twice?
    	// @ TODO: Learn how to throw errors reasonably in c++ - Odell
        return false;
    }

    else
    {
    	// Add the mapping from hardware target enum to the specified com port.
    	this->hardware_map->insert(make_pair(hardware_target, comPort));

    	// When we attach hardware, we want to be able to enqueue messages to that piece of hardware.
    	// Thus, we have a mashmap that goes from Hardware to a queue associated with messages to that hardware.
    	queue<Message*> *msg_queue = new queue<Message*>;
    	this->msg_queue_map->insert(make_pair(hardware_target, msg_queue));

    }

    return true;
}

void Communicator::sendNextMsg(Hardware hardware_target) {
    // @TODO: We need to check for .empty() before we ever try
    // to access .front or .pop
    
    // Open up the associated hardware to send a message
    std::ofstream arduino;
	arduino.open(this->hardware_map->at(hardware_target));  //ex "/dev/ttyXXXX" 

    
    // Send a message to the arduino from the queue associated with it's hardware name
    arduino << this->msg_queue_map->at(hardware_target)->front()->write();
    this->msg_queue_map->at(hardware_target)->pop();


    return;
}

void Communicator::readData() {
    return;
}

void Communicator::queueMsg(Message* msg) {
    // TODO: Error checking for if the msg hardware isnt attached
    // Do we then attach it, or throw up an error to be handled at a higher level?
    this->msg_queue_map->at(msg->getHardware())->push(msg);
    return;
}

