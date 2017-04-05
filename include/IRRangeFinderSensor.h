#include "IRangeFinderSensor.h"

class IRRangeFinderSensor : public IRangeFinderSensor {

    public:
        void updateSensor() override;
        double getDistanceMM() override;
        double getDistanceCM() override;
};
