#pragma once

#if __linux__
    #include <wiringPi.h>
#elif __unix__
    #include <wiringPi.h>
#else
    #include "../wiringPiMock/wiringPi.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include <map>

#include "thread.h"
#include "ISensorManager.h"
#include "SensorManager.h"
#include "Communicator.h"
#include "Message.h"
#include "RawSensorData.h"
#include "CommandManager.h"
#include "MockIRRangeFinderSensor.h"
