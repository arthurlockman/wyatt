//
// Created by Tucker Haydon on 4/9/17.
//

#include "include/MockSensorManager.h"

MockSensorManager::MockSensorManager() : ISensorManager() {

};

MockSensorManager::~MockSensorManager() {

};

void MockSensorManager::addSensor(Hardware hardware, ISensor* sensor) {

};

void MockSensorManager::updateSensors(std::list<IMessage*>* messages) {
    this->updateMessages = messages;
};

std::list<IMessage*>* MockSensorManager::getUpdateMessages() {
    return this->updateMessages;
}