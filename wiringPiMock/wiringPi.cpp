#include "wiringPi.h"
#include <iostream>

int wiringPiSetupSys(void) {
    std::cout <<  "WiringPi Setup." << std::endl;
    return 0;
}

int wiringPiSetupGpio(void) {
    std::cout <<  "WiringPi Setup." << std::endl;
    return 0;
}

int wiringPiSetup(void) {
    std::cout <<  "WiringPi Setup." << std::endl;
    return 0;
}

void pinMode(int pin, int mode) {
    std::cout <<  "Set pin mode: pin " << pin << " to mode: " << mode << std::endl;
}

void digitalWrite(int pin, int value) {
    std::cout << "Digital wrote pin " << pin << " " << value << std::endl;
}

void pullUpDnControl(int pin, int pud) {
    std::cout << "Changed pullup on pin " << pin << " " << pud << std::endl;
}

int digitalRead(int pin) {
    return HIGH;
}

void pwmWrite(int pin, int value) {
    std::cout << "PWM wrote pin " << pin << " " << value << std::endl;

}

void digitalWriteByte(int value) {

}

unsigned int millis(void) {
    return 0;
}

void delay(unsigned int howLong) {

}

void delayMicroseconds(unsigned int howLong) {

}
