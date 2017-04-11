#include "SerialPort.h"

SerialPort::SerialPort(const char *path, int baudRate) {
    this->path = path;
    this->baudRate = baudRate;
};

int SerialPort::begin() {
  //  struct termios options;
  //  speed_t myBaud;
  //  int status;
/*
    switch (baudRate) {
        case 9600:
            myBaud = B9600;
            break;
        case 115200:
            myBaud = B115200;
            break;

        default:
            return -2;
    }
*/
    // if ((fd = open(path, O_RDWR | O_NOCTTY | O_NDELAY)) == -1)
    //    return -1;

    //fcntl(fd, F_SETFL, O_RDWR);

// Get and modify current options:

    // tcgetattr(fd, &options);

    // options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate
    // options.c_iflag = IGNPAR;
    // options.c_oflag = 0;
    // options.c_lflag = 0;
    // tcflush(fd, TCIFLUSH);
    // tcsetattr(fd, TCSANOW, &options);

    // cfmakeraw(&options);
    // cfsetispeed(&options, myBaud);
    // cfsetospeed(&options, myBaud);

    // options.c_cflag |= (CLOCAL | CREAD);
    // options.c_cflag |= (CLOCAL | CREAD);
    // options.c_cflag &= ~PARENB;
    // options.c_cflag &= ~CSTOPB;
    // options.c_cflag &= ~CSIZE;
    // options.c_cflag |= CS8;
    // options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    // options.c_oflag &= ~OPOST;

    // options.c_cc[VMIN] = 0;
    // options.c_cc[VTIME] = 1;    // 0.1 second

    // tcsetattr(fd, TCSANOW, &options);

    // ioctl(fd, TIOCMGET, &status);

    // status |= TIOCM_DTR;
    // status |= TIOCM_RTS;

    // ioctl(fd, TIOCMSET, &status);

    // usleep(10000);    // 10mS
    //

    fd = open(path, O_RDWR | O_NOCTTY | O_NDELAY);
            
    struct termios options;
    tcgetattr(fd, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    return fd;
};

void SerialPort::writeData(const char *bytes, int numBytes) {
    int count = write(fd, bytes, numBytes);
    std::cout << "Bytes written: " << count << std::endl;
};

bool SerialPort::canRead() {
    int result;

    if (ioctl(fd, FIONREAD, &result) == -1)
        return -1;
    return result;
};

Message *SerialPort::readData() {

    char packetType = getChar();
    Hardware hardwareType = HARDWARE_MAP[packetType];
    char messageLength = hardwareType.messageLength;

    char buffer[messageLength];

    for (int i = 0; i < messageLength; i++) {
        while (!canRead());
        buffer[i] = getChar();
    }

    std::cout << "Packet Type: " << (int)packetType << std::endl;
    return new Message(hardwareType, buffer);
};

char SerialPort::getChar() {
    uint8_t x;

    if (read(fd, &x, 1) != 1)
        return -1;

    return ((int) x) & 0xFF;
}

void SerialPort::end() {
    close(fd);
};
