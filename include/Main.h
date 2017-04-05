#pragma once

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>

#include "thread.h"
#include "ISensorManager.h"
#include "SensorManager.h"
#include "Communicator.h"
#include "Message.h"
#include "RawSensorData.h"
#include "MockIRRangeFinderSensor.h"
