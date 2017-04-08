#pragma once

/*
* A struct containing information relevant to the hardware on the robot.
*/
struct Hardware
{
    /* An address from 0-255. Must be unique */
    unsigned char address;

    /* The length of messages in bytes required to communicate to/from the hardware */
    unsigned char messageLength;
};

/* Required to use the hardware in an std::map */
bool operator < (const Hardware &a, const Hardware &b);

/* ENSURE HARDWARE IS APPENDED */
extern const Hardware HARDWARE_MAP[];

/* DECLARE ALL HARDWARE HERE */
extern const Hardware H_RIGHT_MOTOR;
extern const Hardware H_LEFT_MOTOR;
extern const Hardware H_MOCK_IR_SENSOR;