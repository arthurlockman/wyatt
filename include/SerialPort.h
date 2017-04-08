#pragma once

#include <iostream>

/* Headers for pi serial communication */
#include <wiringPi.h>
#include <wiringSerial.h>

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
