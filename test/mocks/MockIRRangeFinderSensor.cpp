#include "include/MockIRRangeFinderSensor.h"
#include "include/MockIRRangeFinderSensorMessage.h"

MockIRRangeFinderSensor::MockIRRangeFinderSensor() {
    // Constructor
}

MockIRRangeFinderSensor::~MockIRRangeFinderSensor() {
    // Destructor
}

void MockIRRangeFinderSensor::updateSensor(IMessage* msg) {
    this->data = ((MockIRRangeFinderSensorMessage*)msg)->getData();
    delete msg;
}

double MockIRRangeFinderSensor::getDistanceCM() {
    // No-Op
    return -1;
}

std::string MockIRRangeFinderSensor::getData() {
    return this->data;
}
