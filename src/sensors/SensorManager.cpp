#include "sensors/SensorManager.h"

SensorManager::SensorManager() : ISensorManager() {
    this->sensorMap = new std::map<Hardware, ISensor*>;
}; 

SensorManager::~SensorManager() {
   delete this->sensorMap; 
};

void SensorManager::addSensor(Hardware hardware, ISensor* sensor) {

    // Ensure that the sensor has not already been added
    if( this->sensorMap->find(hardware) != this->sensorMap->end() ) {
        throw DuplicateHardwareException(hardware);
    }
    this->sensorMap->insert(std::make_pair(hardware, sensor));
};

void SensorManager::updateSensors(std::list<IMessage*>* messages) {

    // For each message, extract the message data and send it to the appropriate sensor.
    for(IMessage* msg: *messages) {

        Hardware hardware = msg->getHardware();
        if( this->sensorMap->find(hardware) == this->sensorMap->end() ) {
            throw NonexistentHardwareException(hardware);
        }

        this->sensorMap->at(msg->getHardware())->updateSensor(msg);
    }

    delete messages;
};
