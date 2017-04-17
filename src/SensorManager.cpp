#include "SensorManager.h"
using namespace std;

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

void SensorManager::updateSensors(list<Message*>* messages) {

    // For each message, extract the message data and send it to the appropriate sensor.
//    for(Message* msg: *messages) {
//        RawSensorData* data = new RawSensorData(msg->getMessage());
//
//        Hardware hardware = msg->getHardware();
//        if( this->sensorMap->find(hardware) == this->sensorMap->end() ) {
//            throw new NonexistentHardwareException(hardware);
//        }
//
//        this->sensorMap->at(msg->getHardware())->updateSensor(data);
//    }
//
//    // Delete the list of messages
//    while(!messages->empty()) {
//        delete messages->front();
//        messages->pop_front();
//    }



//    for(Message* msg: *messages) {
//        std::cout << msg->getMessage() << std::endl;
//    }
};
