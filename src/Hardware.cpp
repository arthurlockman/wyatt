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

const Hardware H_RIGHT_ENCODER = { 
        .address = RIGHT_ENCODER_ADDRESS,
        .messageLength = 8,
};

const Hardware H_LEFT_ENCODER = { 
        .address = LEFT_ENCODER_ADDRESS,
        .messageLength = 8,
};

const Hardware HARDWARE_MAP[] = {
    H_RIGHT_MOTOR,
    H_LEFT_MOTOR,
    H_LEFT_ENCODER,
    H_RIGHT_ENCODER
};
