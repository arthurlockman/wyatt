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

bool SerialPort::canRead() {
    return serialDataAvail(this->fileDescriptor);
};

Message* SerialPort::read() {

    char packetType = (char)serialGetchar(this->fileDescriptor);
    Hardware hardwareType = HARDWARE_MAP[packetType];
    char messageLength = hardwareType.messageLength;

    char buffer[messageLength];

    for(int i = 0; i < messageLength; i++) {
        buffer[i] = (char)serialGetchar(this->fileDescriptor);
    }

    return new Message(hardwareType, buffer);
};

void SerialPort::close() {
    serialClose(this->fileDescriptor);
};
