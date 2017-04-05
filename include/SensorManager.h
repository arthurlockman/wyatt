#include "ISensorManager.h"
#include "ISensor.h"
#include <list>

using namespace std;
class SensorManager : public ISensorManager {

    public:
        SensorManager(list<ISensor*>* sensors);
        ~SensorManager() override;
        void updateSensors() override;
};
