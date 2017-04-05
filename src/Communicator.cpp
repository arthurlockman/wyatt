#include "Communicator.h"

Communicator::Communicator(ISensorManager* sensorManager) {
    this->sensorManager = sensorManager;

    //Map for all hardware attachments to their communication ports.
    this->hardware_map = new map<Hardware, string>;  

    //Map of Hardware attachments to their message queue. 
    this->msg_queue_map = new map<Hardware, queue<Message*>*>;
}


class CommunicationException: public exception
{
  virtual const char* what() const throw()
  {
    return "An exception has occurred in our communication thread.";
  }
} commException;


bool Communicator::attachArduino (string comPort, Hardware hardware_target) {
	// Check if hardware key already exists within our map of hardware->communication port
    if (this->hardware_map->find(hardware_target) != this->hardware_map->end())
    {
    	// You can't reattach this, and this comPort is already attached to a piece of hardware!
        throw commException;
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
    
    if(this->msg_queue_map->at(hardware_target)->empty())
    {
        throw commException;
        return;
    }

    // Open up the associated hardware to send a message
    std::ofstream arduino;
	arduino.open(this->hardware_map->at(hardware_target));  //ex "/dev/ttyXXXX" 

    
    // Send a message to the arduino from the queue associated with it's hardware name
    arduino << this->msg_queue_map->at(hardware_target)->front()->getMessage();
    this->msg_queue_map->at(hardware_target)->pop();

    return;
}

void Communicator::readData() {
    return;
}

void Communicator::queueMsg(Message* msg) {
    //Attempt to enqueue the message. If we can't, then throw an error because there's not a queue for that message's associated hardware. 
    try {
        this->msg_queue_map->at(msg->getHardware())->push(msg);// Push message into queue specified by hardware
        return;
    }
    catch (const out_of_range oor_map) {
        throw commException;
    }
}

