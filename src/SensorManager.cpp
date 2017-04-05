#include "SensorManager.h"

SensorManager::SensorManager(list<ISensor*>* sensors) : ISensorManager(sensors) {}; 

SensorManager::~SensorManager() {

};

void SensorManager::updateSensors() {

};
