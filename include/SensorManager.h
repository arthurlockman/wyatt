#include "ISensorManager.h"
#include "ISensor.h"
#include <list>
#include <map>
#include "Hardware.h"
#include "Message.h"

using namespace std;
class SensorManager : public ISensorManager {

    public:
        SensorManager(map<Hardware, ISensor*>* sensorMap);
        ~SensorManager() override;
        void updateSensors(list<Message*>* messages) override;
};
