#pragma once

/*
This enumerates the various pieces of hardware on the robot. Messages sent to the robot must be destined for one of the pieces of hardware.
*/

struct Hardware
{
    unsigned char address;
    unsigned char messageLength;
};

bool operator < (const Hardware &a, const Hardware &b);

/* ENSURE HARDWARE IS APPENDED */
extern const Hardware HARDWARE_MAP[];

/* DECLARE ALL HARDWARE HERE */
extern const Hardware H_RIGHT_MOTOR;
extern const Hardware H_LEFT_MOTOR;
extern const Hardware H_MOCK_IR_SENSOR;