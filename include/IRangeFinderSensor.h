#include "ISensor.h"

class IRangeFinderSensor : public ISensor {

    public:
        virtual void updateSensor() override = 0;
        virtual double getDistanceMM() = 0;
        virtual double getDistanceCM() = 0;
};
