#include "IRangeFinderSensor.h"

class IRRangeFinderSensor : public IRangeFinderSensor {

    public:
        virtual void updateSensor();
        virtual double getDistanceMM();
        virtual double getDistanceCM();
};
