#include "SerialPort.h"

SerialPort::SerialPort(const char* path, int baudRate) {
    this->path=path;
    this->baudRate = baudRate;
};

void SerialPort::open() {
    this->fileDescriptor=serialOpen(this->path, this->baudRate);
    serialFlush(this->fileDescriptor);
};

void SerialPort::write(char* bytes, int numBytes) {
    for(int i = 0; i < numBytes; i++) {
        serialPutchar(this->fileDescriptor, bytes[i]);
    }
};

bool SerialPort::canRead() {
    int avail = serialDataAvail(this->fileDescriptor);
    if(avail != 0) {
        std::cout << "Data!" << std::endl;
    }
    return avail;
};

Message* SerialPort::read() {

    char packetType = (char)serialGetchar(this->fileDescriptor);
    Hardware hardwareType = HARDWARE_MAP[packetType];
    char messageLength = hardwareType.messageLength;

    char buffer[messageLength];

    for(int i = 0; i < messageLength; i++) {
        while(!canRead());
        buffer[i] = (char)serialGetchar(this->fileDescriptor);
    }

    return new Message(hardwareType, buffer);
};

void SerialPort::close() {
    serialClose(this->fileDescriptor);
};
