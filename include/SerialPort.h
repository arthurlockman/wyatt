#pragma once

/* Headers for pi serial communication */
#include <wiringPi.h>
#include <wiringSerial.h>

class SerialPort {
public:
    SerialPort(char* path, int baudRate);
    bool open();
    void write(char* bytes, int numBytes);
    std::string read(int numBytes);
    void close();


private:
    int fileDescriptor;
    int baudRate;
    char* path;
};