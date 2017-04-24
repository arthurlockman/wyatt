//
// Created by Arthur Lockman on 4/23/17.
//

#pragma once

#ifdef IS_RASPI
    #include <wiringPi.h>
    #include <wiringPiI2C.h>
#else
    #include "../wiringPiMock/wiringPi.h"
    #include "../wiringPiMock/wiringPiI2C.h"
#endif
