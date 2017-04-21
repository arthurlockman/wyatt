#pragma once

#include "MotorController.h"

#ifdef IS_RASPI
    #include <wiringPi.h>
    #include <wiringPiI2C.h>
#else
    #include "../wiringPiMock/wiringPi.h"
    #include "../wiringPiMock/wiringPiI2C.h"
#endif

// Registers
#define PCA9685_ADDRESS     0x40
#define MODE1               0x00
#define MODE2               0x01
#define SUBADR1             0x02
#define SUBADR2             0x03
#define SUBADR3             0x04
#define PRESCALE            0xFE
#define LED0_ON_L           0x06
#define LED0_ON_H           0x07
#define LED0_OFF_L          0x08
#define LED0_OFF_H          0x09
#define ALL_LED_ON_L        0xFA
#define ALL_LED_ON_H        0xFB
#define ALL_LED_OFF_L       0xFC
#define ALL_LED_OFF_H       0xFD

// Bits
#define RESTART             0x80
#define SLEEP               0x10
#define ALLCALL             0x01
#define INVRT               0x10
#define OUTDRV              0x04

/**
 * This class controls an Adafruit PWM/Servo Raspberry
 * Pi Hat.
 *
 * I2C specific functions adapted from:
 * https://github.com/adafruit/Adafruit_Python_PCA9685/blob/master/Adafruit_PCA9685/PCA9685.py
 */
class AdafruitPWMServoHat: public MotorController {
public:
    /**
     * Constructs an Adafruit PWM/Servo Driver Hat controller.
     * This will also configure the proper I2C communication
     * channels for the device.
     *
     * @param pwmFrequency PWM frequency to set (default is 60)
     */
    AdafruitPWMServoHat(int pwmFrequency = 60);
    /**
     * Destruct the driver object.
     */
    ~AdafruitPWMServoHat();
    /**
     * Set a motor or servo on the HAT.
     *
     * @param motorID Motor ID, from 0-15 (mapped to the outputs on the baord.
     * @param speed The speed (0-255) to set the motor to.
     *
     * @return true if successful.
     */
    bool setMotor(int motorID, int speed);
    /**
     * Stop a specific motor/servo on the HAT. 
     *
     * @param motorID Motor ID, from 0-15 (mapped to the outputs on the baord.
     *
     * @return true if successful.
     */
    bool stopMotor(int motorID);
    /**
     * Stop all motors on the HAT.
     *
     * @return true if successful.
     */
    bool stopAllMotors();
    /**
     * Set a PWM channel to a specific on/off time.
     *
     * @param channel Channel to write to.
     * @param on On time
     * @param off Off time
     */
    void setPwm(int channel, int on, int off);
    /**
     * Set all PWM channels to a specific on/off time.
     *
     * @param on On time
     * @param off Off time
     */
    void setAllPwm(int on, int off);
private:
    //! I2C device file descriptor
    int m_i2c;
    //! PWM Frequency setting (default is 60)
    int m_hz;
    /**
     * Sends a software reset to all servo drivers on the bus.
     */
    void softwareReset();
    /**
     * Set the PWM driver frequency in Hz.
     *
     * @param freqHz Frequency (Hz)
     */
    void setPwmFrequency(double freqHz);
};

