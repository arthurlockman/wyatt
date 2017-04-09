#pragma once

#include <iostream>

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
    void open();
    void write(char* bytes, int numBytes);
    std::string read(int numBytes);
    void close();


private:
    int fileDescriptor;
    int baudRate;
    const char* path;
};
