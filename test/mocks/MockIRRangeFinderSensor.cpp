#include "MockIRRangeFinderSensor.h"

MockIRRangeFinderSensor::MockIRRangeFinderSensor() {
    // Constructor
}

MockIRRangeFinderSensor::~MockIRRangeFinderSensor() {
    // Destructor
}

void MockIRRangeFinderSensor::updateSensor(RawSensorData* data) {
    this->data = data->getData();
    delete data;
}

double MockIRRangeFinderSensor::getDistanceCM() {
    // No-Op
    return -1;
}

std::string MockIRRangeFinderSensor::getData() {
    return this->data;
}
