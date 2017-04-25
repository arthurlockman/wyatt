#include "Communicator.h"

Communicator::Communicator(ISensorManager* sensorManager, IHardwareInterface* hardwareInterface) : Thread() {
    this->sensorManager = sensorManager;
    this->hardwareInterface = hardwareInterface;

    this->messageQueue = new std::list<IMessage*>;
}

Communicator::~Communicator() {
    delete this->sensorManager;
    delete this->hardwareInterface;
    delete this->messageQueue;
}

void Communicator::queueMessage(IMessage *msg) {
    this->messageQueue->push_back(msg);
}

void Communicator::queueMessage(std::list<IMessage*>* messages) {
    for(IMessage* msg: *messages) {
        this->queueMessage(msg);
    }
}

void Communicator::write() {
    while (!this->messageQueue->empty())
    {
        this->hardwareInterface->write(this->messageQueue->front());
        this->messageQueue->pop_front();
    }
}

void Communicator::read() {
    this->sensorManager->updateSensors(this->hardwareInterface->read());
}

void* Communicator::run() {
    while(!m_signal) {

        // Write any data
        this->write();

        // Read any data
        this->read();

    }
    return NULL;
}

