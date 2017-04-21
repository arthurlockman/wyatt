#include "RawSensorData.h"

RawSensorData::RawSensorData(std::string data) {
    this->data = data;
};

RawSensorData::~RawSensorData() {
    // No-Op
};

std::string RawSensorData::getData() {
    return this->data;
};
