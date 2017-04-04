include "IRangeFinderSensor.h"

class IRRangeFinderSensor : public IRangeFinderSensor {

    public:
        virtual void updateSensr();
        virtual double getDistanceMM();
        virtual double getDistanceCM();
};
