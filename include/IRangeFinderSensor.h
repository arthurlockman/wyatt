#include "ISensor.h"

class RangeFinderSensor : public ISensor {

    public:
        virtual void updateSensor() = 0;
        virtual double getDistanceMM() = 0;
        virtual double getDistanceCM() = 0;
};
