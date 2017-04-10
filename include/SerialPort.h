#pragma once

#include "Hardware.h"
#include "Message.h"

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
    bool canRead();
    Message* read();
    void close();


private:
    int fileDescriptor;
    int baudRate;
    const char* path;
};
