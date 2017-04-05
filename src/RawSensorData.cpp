#include "RawSensorData.h"

RawSensorData::RawSensorData(string data) {
    this->data = data;
};

string RawSensorData::getData() {
    return this->data;
};
