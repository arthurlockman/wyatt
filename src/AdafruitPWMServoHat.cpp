#include "AdafruitPWMServoHat.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <cmath>

AdafruitPWMServoHat::AdafruitPWMServoHat(int pwmFrequency):
    m_hz(pwmFrequency)
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

    this->setPwmFrequency((double)m_hz);
}

AdafruitPWMServoHat::~AdafruitPWMServoHat()
{
}

bool AdafruitPWMServoHat::setMotor(int motorID, int speed)
{
    speed = (speed > 4095) ? 4095 : (speed < 0) ? 0 : speed;
    this->setPwm(motorID, 0, speed);
    return true;
}

bool AdafruitPWMServoHat::stopMotor(int motorID)
{
    this->setMotor(motorID, 0);
    return true;
}

bool AdafruitPWMServoHat::stopAllMotors()
{
    for (int i = 0; i < 16; i++)
    {
        this->stopMotor(i);
    }
    return true;
}

void AdafruitPWMServoHat::softwareReset()
{
    wiringPiI2CWrite(m_i2c, 0x06); // Software Reset 
}

void AdafruitPWMServoHat::setPwmFrequency(double freqHz)
{
    double prescaleval = 25000000.0;
    prescaleval /= 4096.0;
    prescaleval /= freqHz;
    prescaleval -= 1.0;
    std::cout << "Setting PWM Frequency to " << freqHz << "Hz" << std::endl;
    std::cout << "Estimated Prescale: " << prescaleval << std::endl;
    int prescale = (int)floor(prescaleval + 0.5);
    std::cout << "Final Prescale: " << prescale << std::endl;
    int oldmode = wiringPiI2CReadReg8(m_i2c, MODE1);
    int newmode = (oldmode & 0x7F) | 0x10;
    wiringPiI2CWriteReg8(m_i2c, MODE1, newmode);
    wiringPiI2CWriteReg8(m_i2c, PRESCALE, prescale);
    wiringPiI2CWriteReg8(m_i2c, MODE1, oldmode);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    wiringPiI2CWriteReg8(m_i2c, MODE1, oldmode | 0x80);
}

void AdafruitPWMServoHat::setPwm(int channel, int on, int off)
{
    wiringPiI2CWriteReg8(m_i2c, LED0_ON_L + 4*channel, on & 0xFF);
    wiringPiI2CWriteReg8(m_i2c, LED0_ON_H + 4*channel, on >> 8);
    wiringPiI2CWriteReg8(m_i2c, LED0_OFF_L + 4*channel, off & 0xFF);
    wiringPiI2CWriteReg8(m_i2c, LED0_OFF_H + 4*channel, off >> 8);
}

void AdafruitPWMServoHat::setAllPwm(int on, int off)
{
    wiringPiI2CWriteReg8(m_i2c, ALL_LED_ON_L, on & 0xFF);
    wiringPiI2CWriteReg8(m_i2c, ALL_LED_ON_H, on >> 8);
    wiringPiI2CWriteReg8(m_i2c, ALL_LED_OFF_L, off & 0xFF);
    wiringPiI2CWriteReg8(m_i2c, ALL_LED_OFF_H, off >> 8);
}
