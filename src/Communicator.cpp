#include "Communicator.h"
#include "hardwareinterface/EncoderAdapter.h"
#include "messages/EncoderMessage.h"
#include <iostream>

Communicator::Communicator(ISensorManager* sensorManager) : Thread() {
    this->sensorManager = sensorManager;
    this->messageMap = new std::map<Hardware, IMessage*>;
    this->hardwareInterfaceMap = new std::map<Hardware, IHardwareInterface*>;
    this->hardwareInterfaces = new std::list<IHardwareInterface*>;
}

Communicator::~Communicator() {
    delete this->sensorManager;
    delete this->messageMap;
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
    m_lock.lock();
    this->messageMap->erase(msg->getHardware());
    this->messageMap->insert(std::make_pair(msg->getHardware(), msg));
    m_lock.unlock();
}

void Communicator::queueMessage(std::list<IMessage*>* messages) {
    for(IMessage* msg: *messages) {
        this->queueMessage(msg);
    }
    delete messages;
}

void Communicator::write() {
    m_lock.lock();
    for (std::map<Hardware,IMessage*>::iterator it=messageMap->begin(); it!=messageMap->end(); ++it) {
        IHardwareInterface* interface = hardwareInterfaceMap->at(it->first);
        interface->write(it->second);
    }
    messageMap->clear();
    m_lock.unlock();
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

