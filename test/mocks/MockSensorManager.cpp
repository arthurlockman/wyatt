//
// Created by Tucker Haydon on 4/9/17.
//

#include "include/MockSensorManager.h"

MockSensorManager::MockSensorManager() : ISensorManager() {
    this->updateMessages = new std::list<IMessage*>;
};

MockSensorManager::~MockSensorManager() {

};

void MockSensorManager::addSensor(Hardware hardware, ISensor* sensor) {

};

void MockSensorManager::updateSensors(std::list<IMessage*>* messages) {

    while(!messages->empty()) {
        IMessage* msg = messages->front();
        this->updateMessages->push_back(msg);
        messages->pop_front();
    }
};

