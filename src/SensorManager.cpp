#include "SensorManager.h"

SensorManager::SensorManager(map<Hardware, ISensor*>* sensorMap) : ISensorManager(sensorMap) {}; 

SensorManager::~SensorManager() {

};

void SensorManager::updateSensors(list<Message*>* messages) {

    // For each message, extract the message data and send it to the appropriate sensor.
    for(Message* msg: *messages) {
        RawSensorData* data = new RawSensorData(msg->getMessage());
        this->sensorMap->at(msg->getHardware())->updateSensor(data);
    }

    // Delete the list of messages
    while(!messages->empty()) {
        delete messages->front();
        messages->pop_front();
    }
};
