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

double MockIRRangeFinderSensor::getDistanceMM() {
    return this->distanceInCm * 10;
}

double MockIRRangeFinderSensor::getDistanceCM() {
    return this->distanceInCm;
}
