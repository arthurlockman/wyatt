#include "Communicator.h"
#include "hardwareinterface/EncoderAdapter.h"
#include "messages/EncoderMessage.h"
#include <iostream>

Communicator::Communicator(ISensorManager* sensorManager) : Thread() {
    this->sensorManager = sensorManager;
    this->messageQueue = new std::list<IMessage*>;
    this->hardwareInterfaceMap = new std::map<Hardware, IHardwareInterface*>;
    this->hardwareInterfaces = new std::list<IHardwareInterface*>;
}

Communicator::~Communicator() {
    delete this->sensorManager;
    delete this->messageQueue;
    delete this->hardwareInterfaceMap;
}

void Communicator::registerHardware(Hardware hardware, IHardwareInterface* interface) {

    if(this->hardwareInterfaceMap->count(hardware) != 0) {
        throw DuplicateHardwareException(hardware);
    }

    this->hardwareInterfaceMap->insert(std::make_pair(hardware, interface));
    this->hardwareInterfaces->push_back(interface);
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
        IMessage* msg = this->messageQueue->front();

        Hardware hardware = msg->getHardware();
        IHardwareInterface* interface = hardwareInterfaceMap->at(hardware);
        interface->write(msg);

        this->messageQueue->pop_front();
    }
}

void Communicator::read() {
    std::list<IMessage*>* messages = new std::list<IMessage*>;

    for (IHardwareInterface* interface : *(this->hardwareInterfaces)) {
        std::list<IMessage*>* msgs = interface->read();
        while(!msgs->empty()) {
            IMessage* msg = msgs->front();
            messages->push_back(msg);
            msgs->pop_front();
        }
        delete msgs;
    }
    this->sensorManager->updateSensors(messages);
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

