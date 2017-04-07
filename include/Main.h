#pragma once

#ifdef IS_RASPI
    #include <wiringPi.h>
#else
    #include "../wiringPiMock/wiringPi.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include <map>

#include "Thread.h"
#include "ISensorManager.h"
#include "SensorManager.h"
#include "Communicator.h"
#include "Message.h"
#include "RawSensorData.h"
#include "CommandManager.h"
#include "MockIRRangeFinderSensor.h"
