#include "ISensor.h"

class IRangeFinderSensor : public ISensor {

    public:
        virtual ~IRangeFinderSensor() override {};
        virtual void updateSensor(RawSensorData* data) override = 0;
        virtual double getDistanceMM() = 0;
        virtual double getDistanceCM() = 0;
};
