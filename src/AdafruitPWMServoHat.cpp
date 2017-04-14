#include "AdafruitPWMServoHat.h"
#include <chrono>
#include <thread>

AdafruitPWMServoHat::AdafruitPWMServoHat()
{
    m_i2c = wiringPiI2CSetup(PCA9685_ADDRESS);
    this->setAllPwm(0, 0);
    wiringPiI2CWriteReg8(m_i2c, MODE2, OUTDRV);
    wiringPiI2CWriteReg8(m_i2c, MODE1, ALLCALL);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    int mode1 = wiringPiI2CReadReg8(m_i2c, MODE1);
    mode1 = mode1 & ~SLEEP;
    wiringPiI2CWriteReg8(m_i2c, MODE1, mode1);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

AdafruitPWMServoHat::~AdafruitPWMServoHat()
{
    //TODO: Finish this stub.
}

bool AdafruitPWMServoHat::setMotor(int motorID, int speed)
{
    //TODO: Finish this stub.
    return true;
}

bool AdafruitPWMServoHat::stopMotor(int motorID)
{
    //TODO: Finish this stub.
    return true;
}

bool AdafruitPWMServoHat::stopAllMotors()
{
    //TODO: Finish this stub.
    return true;
}

void AdafruitPWMServoHat::softwareReset() {
    wiringPiI2CWrite(m_i2c, 0x06); // Software Reset 
}

void AdafruitPWMServoHat::setPwmFrequency(float freqHz){}
void AdafruitPWMServoHat::setPwm(int channel, char on, char off){}
void AdafruitPWMServoHat::setAllPwm(char on, char off){}
