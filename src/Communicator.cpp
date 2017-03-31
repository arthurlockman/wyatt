#include "Communicator.h"

Communicator::Communicator(ISensorManager* sensorManager) {
    this->sensorManager = sensorManager;
    this->outBuffer = new std::queue<Message>;
}

bool Communicator::attachArduino (string comPort) {

}

void Communicator::sendData() {

}

void Communicator::readData() {

}
