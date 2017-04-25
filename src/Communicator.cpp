#include "Communicator.h"

Communicator::Communicator(ISensorManager* sensorManager) : Thread() {
    this->sensorManager = sensorManager;
    this->messageQueue = new std::list<Message*>;
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

void Communicator::queueMessage(Message *msg) {
    this->messageQueue->push_back(msg);
}

void Communicator::queueMessage(std::list<Message*>* messages) {
    for(Message* msg: *messages) {
        this->queueMessage(msg);
    }
}

void Communicator::write() {
    while (!this->messageQueue->empty())
    {
        Message* msg = this->messageQueue->front();

        Hardware hardware = msg->getHardware();
        IHardwareInterface* interface = hardwareInterfaceMap->at(hardware);
        interface->write(msg);

        this->messageQueue->pop_front();
    }
}

void Communicator::read() {
    std::list<Message*>* messages = new std::list<Message*>;

    for (IHardwareInterface* interface : *(this->hardwareInterfaces)) {
        std::list<Message*>* msgs = interface->read();
        while(!msgs->empty()) {
            Message* msg = msgs->front();
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

