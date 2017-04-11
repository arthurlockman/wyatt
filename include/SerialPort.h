#pragma once

#include "Hardware.h"
#include "Message.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Headers for pi serial communication */
#ifdef IS_RASPI
    #include <wiringPi.h>
    #include <wiringSerial.h>
#else
    #include "../wiringPiMock/wiringPi.h"
    #include "../wiringPiMock/wiringSerial.h"
#endif


class SerialPort {
public:
    SerialPort(const char* path, int baudRate);

    int begin();
    void end();

    void writeData(const char* bytes, int numBytes);
    Message* readData();
    bool canRead();



private:
    int fd;
    int baudRate;
    const char* path;

    char getChar();
    void putChar(const char c);
};
