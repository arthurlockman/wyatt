#include "Communicator.h"

Communicator::Communicator(ISensorManager* sensorManager, ) {
    this->sensorManager = sensorManager;
    this->outBuffer = new queue<Message*>;

    std::map<std::Hardware, string> hardware_map; // Map for all hardware attachments to their associated com port. 
    std::map<std::Hardware, queue<Message*>> msg_queue_map; // Map of Hardware attachments to their message queues.
}

bool Communicator::attachArduino (string comPort, Hardware hardware_target) {

	// Check if key is present. If it is, fail.
    if (hardware_map.find(comPort) != hardware_map.end())
    {
    	// You can't reattach this, and this comPort is already attached to a piece of hardware!
    	// Are you attaching the same component twice?
    	// @ TODO: Learn how to throw errors reasonably in c++ - Odell
    }

    else
    {
    	// Add the mapping from hardware target enum to the specified com port.
    	this->hardware_map[hardware_target] = comPort;

    	// When we attach hardware, we want to be able to enqueue messages to that piece of hardware.
    	// Thus, we have a mashmap that goes from Hardware to a queue associated with messages to that hardware.
    	msg_queue = new queue<Message*>;
    	this->msg_queue_map[hardware_target] = msg_queue;

    }
}

void Communicator::sendNextMsg() {
    // @TODO: We need to check for .empty() before we ever try
    // to access .front or .pop

    // @TODO: How do we want to manage errors in C++? 
    if(!outBuffer.isEmpty())
    {
    	cout << this->outBuffer->front()->write() << endl;
    	this->outBuffer->pop();
	}
}

void Communicator::readData() {

}

void Communicator::queueMsg(Message* msg) {
    this->outBuffer->push(msg);
}
