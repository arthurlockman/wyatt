#include "sensors/IRangeFinderSensor.h"

/**
 * Mocks out an IRRangeFinderSensor to check the data injected into it.
 */
class MockIRRangeFinderSensor : public IRangeFinderSensor {

public:
    MockIRRangeFinderSensor();
    ~MockIRRangeFinderSensor() override;
    void updateSensor(IMessage* msg) override;
    double getDistanceCM() override;
    std::string getData();

private:
    double distanceInCm;
    std::string data;
};
