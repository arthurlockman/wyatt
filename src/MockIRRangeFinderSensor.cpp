#include "MockIRRangeFinderSensor.h"

MockIRRangeFinderSensor::~MockIRRangeFinderSensor() {
}

void MockIRRangeFinderSensor::updateSensor(RawSensorData* data) {
    this->distanceInCm = std::stod(data->getData());
}

double MockIRRangeFinderSensor::getDistanceMM() {
    return this->distanceInCm * 10;
}

double MockIRRangeFinderSensor::getDistanceCM() {
    return this->distanceInCm;
}
