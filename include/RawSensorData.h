#pragma once
#include <string>

/**
 * Wrapper class for data between the ISensorManager and an ISensor.
 */
class RawSensorData {
public:
    /**
     * Constructor.
     * @param data String measurement data
     */
    RawSensorData(std::string data);

    /**
     * Deconstructor. Deletes all pointers.
     */
    ~RawSensorData();

    /**
     * Returns the String measurement data
     * @return String measurement data.
     */
    std::string getData();

private:
    std::string data;
};
