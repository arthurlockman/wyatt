#include "IRangeFinderSensor.h"

class MockIRRangeFinderSensor : public IRangeFinderSensor {

    public:
        MockIRRangeFinderSensor();
        ~MockIRRangeFinderSensor() override;
        void updateSensor(RawSensorData* data) override;
        double getDistanceMM() override;
        double getDistanceCM() override;

    private:
        double distanceInCm;
};
