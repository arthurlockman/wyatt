#include "MockIRRangeFinderSensor.h"

MockIRRangeFinderSensor::MockIRRangeFinderSensor() {
    // Constructor
}

MockIRRangeFinderSensor::~MockIRRangeFinderSensor() {
    // Destructor
}

void MockIRRangeFinderSensor::updateSensor(RawSensorData* data) {
    this->distanceInCm = std::stod(data->getData());
    delete data;
}

double MockIRRangeFinderSensor::getDistanceCM() {
    return this->distanceInCm;
}
