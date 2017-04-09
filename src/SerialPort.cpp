#include "SerialPort.h"
#include <iostream>
using namespace std;

SerialPort::SerialPort(const char* path, int baudRate) {
    this->path=path;
    this->baudRate = baudRate;
};

void SerialPort::open() {
    this->fileDescriptor=serialOpen(this->path, this->baudRate);
};

void SerialPort::write(char* bytes, int numBytes) {
    for(int i = 0; i < numBytes; i++) {
        serialPutchar(this->fileDescriptor, bytes[i]);
    }
};

string SerialPort::read(int numBytes) {

    // TODO

    // char* inBuffer;
    // while(serialDataAvail(this->fileDescriptor) != -1) {
    //     char next = (char)serialGetchar(this->fileDescriptor);
    // }
    return string("");
};

void SerialPort::close() {
    serialClose(this->fileDescriptor);
};
