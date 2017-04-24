#include "Hardware.h"

bool operator < (const Hardware &a, const Hardware &b) 
{ 
    return a.address < b.address;
};

bool operator == (const Hardware &a, const Hardware &b)
{
    return (a.address == b.address) && (a.messageLength == b.messageLength);
};

const Hardware H_RIGHT_MOTOR = { 
        .address = RIGHT_MOTOR_ADDRESS,
        .messageLength = 1,
};

const Hardware H_LEFT_MOTOR = { 
        .address = LEFT_MOTOR_ADDRESS,
        .messageLength = 1,
};

const Hardware HARDWARE_MAP[] = {
    H_RIGHT_MOTOR,
    H_LEFT_MOTOR
};
