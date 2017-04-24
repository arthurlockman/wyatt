#include "IRangeFinderSensor.h"

class MockIRRangeFinderSensor : public IRangeFinderSensor {

public:
    MockIRRangeFinderSensor();
    ~MockIRRangeFinderSensor() override;
    void updateSensor(RawSensorData* data) override;
    double getDistanceCM() override;
    std::string getData();

private:
    double distanceInCm;
    std::string data;
};
