#pragma once

#ifdef IS_RASPI
    #include <wiringPi.h>
    #include <wiringPiI2C.h>
#else
    #include "../wiringPiMock/wiringPi.h"
    #include "../wiringPiMock/wiringPiI2C.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include <map>
#include <iostream>
#include <string>

#include "Thread.h"
#include "ISensorManager.h"
#include "SensorManager.h"
#include "Communicator.h"
#include "Message.h"
#include "RawSensorData.h"
#include "CommandManager.h"
#include "Hardware.h"
#include "AdafruitPWMServoHat.h"
#include "Chassis.h"
#include "commands/DriveForwardSecondsCommand.h"
