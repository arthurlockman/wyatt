#include "IRangeFinderSensor.h"

class IRRangeFinderSensor : public IRangeFinderSensor {

    public:
        ~IRRangeFinderSensor() override;
        void updateSensor() override;
        double getDistanceMM() override;
        double getDistanceCM() override;
};
