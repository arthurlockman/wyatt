
Motor::Motor(int forwardPin, int backwardPin) {
    this->forwardPin = forwardPin;
    this->backwardPin = backwardPin;

    pinMode(forwardPin, OUTPUT);
    pinMode(backwardPin, OUTPUT);
};

void Motor::drive(double speed, int direction) {
    int pwm = mapDoubleToInt(speed, 0.0, 1.0, 0, 255);

    if(direction == FORWARDS) {
        analogWrite(this->forwardPin, pwm);
        analogWrite(this->backwardPin, 0);
    } else if(direction == BACKWARDS) {
        analogWrite(this->backwardPin, pwm);
        analogWrite(this->forwardPin, 0);
    }
};

