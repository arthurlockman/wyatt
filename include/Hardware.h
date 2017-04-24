#pragma once

#define RIGHT_MOTOR_ADDRESS     ((unsigned char) 0b00000000)
#define LEFT_MOTOR_ADDRESS      ((unsigned char) 0b00000001)

/**
 * Struct containing data specific to a piece of hardware
 */
struct Hardware
{
    /* A unique byte address */
    unsigned char address;

    /* The length of the message (excluding the byte address) */
    unsigned char messageLength;
};

/* Comparision function required for maps */
bool operator < (const Hardware &a, const Hardware &b);
bool operator == (const Hardware &a, const Hardware &b);

/* ENSURE HARDWARE IS APPENDED */
extern const Hardware HARDWARE_MAP[];

/* DECLARE ALL HARDWARE HERE */
extern const Hardware H_RIGHT_MOTOR;
extern const Hardware H_LEFT_MOTOR;
