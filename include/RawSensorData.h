#pragma once
#include <string>

/*
 * Wrapper class for data transmitted from the arduino/sensors to the sensor objects on the raspi.
 */
using namespace std;
class RawSensorData {
public:
    RawSensorData(string data);   
    string getData();

private:
    string data;
};
