#include "RawSensorData.h"

RawSensorData::RawSensorData(std::string data) {
    this->data = data;
};

RawSensorData::~RawSensorData() {
    // TODO
    // Delete/free string?
};

std::string RawSensorData::getData() {
    return this->data;
};
