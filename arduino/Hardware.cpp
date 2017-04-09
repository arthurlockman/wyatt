#include "Hardware.h"

bool operator < (const Hardware &a, const Hardware &b) 
{ 
    return a.address < b.address;
};

const Hardware H_RIGHT_MOTOR = { 
        .address = '0',
        .messageLength = 1,
};

const Hardware H_LEFT_MOTOR = { 
        .address = '1',
        .messageLength = 1,
};

const Hardware H_MOCK_IR_SENSOR = { 
        .address = '2',
        .messageLength = 1,
};

const Hardware HARDWARE_MAP[] = {
    H_RIGHT_MOTOR,
    H_LEFT_MOTOR,
    H_MOCK_IR_SENSOR
};