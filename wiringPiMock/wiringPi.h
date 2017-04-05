//
// Created by Arthur Lockman on 4/5/17.
//

#ifndef WYATT_WIRINGPI_H
#define WYATT_WIRINGPI_H

#include <sys/time.h>

#define HIGH 1
#define LOW 0

#define INPUT 1
#define OUTPUT 2
#define PWM_OUTPUT 3
#define PUD_OFF 0
#define PUD_DOWN 1
#define PUD_UP 2

// Setup Functions
int wiringPiSetup(void);
int wiringPiSetupGpio(void);
int wiringPiSetupSys(void);

// Wiring Functions
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
void digitalWriteByte(int value);
void pwmWrite(int pin, int value);
int digitalRead(int pin);
void pullUpDnControl(int pin, int pud);

// Timing
/**
 * This returns a number representing the number if milliseconds since your program called one of the wiringPiSetup
 * functions. It returns an unsigned 32-bit number which wraps after 49 days.
 * @return
 */
unsigned int millis(void);
void delay(unsigned int howLong);
void delayMicroseconds(unsigned int howLong);
#endif
