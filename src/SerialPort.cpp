#include "SerialPort.h"

SerialPort::SerialPort(const char *path, int baudRate) {
    this->path = path;
    this->baudRate = baudRate;
};

int SerialPort::begin() {
    struct termios options;
    speed_t myBaud;
    int status;

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

    if ((fd = open(path, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1)
        return -1;

    fcntl(fd, F_SETFL, O_RDWR);

// Get and modify current options:

    tcgetattr(fd, &options);

    cfmakeraw(&options);
    cfsetispeed(&options, myBaud);
    cfsetospeed(&options, myBaud);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 100;    // Ten seconds (100 deciseconds)

    tcsetattr(fd, TCSANOW, &options);

    ioctl(fd, TIOCMGET, &status);

    status |= TIOCM_DTR;
    status |= TIOCM_RTS;

    ioctl(fd, TIOCMSET, &status);

    usleep(10000);    // 10mS

    return fd;
};

void SerialPort::writeData(const char *bytes, int numBytes) {
    for (int i = 0; i < numBytes; i++) {
        this->putChar(bytes[i]);
    }
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

    return new Message(hardwareType, buffer);
};

char SerialPort::getChar() {
    uint8_t x;

    if (read(fd, &x, 1) != 1)
        return -1;

    return ((int) x) & 0xFF;
}

void SerialPort::putChar(const char c) {
    write(fd, &c, 1);
}

void SerialPort::end() {
    close(fd);
};
