#include "RawSensorData.h"

using namespace std;

RawSensorData::RawSensorData(string data) {
    this->data = data;
};

RawSensorData::~RawSensorData() {
    // TODO
    // Delete/free string?
};

string RawSensorData::getData() {
    return this->data;
};
