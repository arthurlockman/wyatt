//
// Created by Tucker Haydon on 4/25/17.
//

#pragma once

#include "Communicator.h"
#include "sensors/SensorManager.h"
#include "sensors/ISensorManager.h"
#include "hardwareinterface/MotorAdapter.h"
#include "hardwareinterface/EncoderAdapter.h"
#include "hardwareinterface/AdafruitPWMServoHat.h"
#include "wiringPiInclude.h"
#include "sensors/EncoderSensor.h"
#include "sensors/ISensor.h"
#include "CommandManager.h"
#include "commands/DriveMotorRPM.h"
#include "commands/DriveRobotCommand.h"

#define RIGHT_MOTOR_FORWARD_PIN 0
#define RIGHT_MOTOR_BACKWARD_PIN 1
#define LEFT_MOTOR_FORWARD_PIN 3
#define LEFT_MOTOR_BACKWARD_PIN 2

#define ENCODER_TICKS_PER_REVOLUTION 64
#define LEFT_ENCODER_PIN_A 1
#define LEFT_ENCODER_PIN_B 2
#define RIGHT_ENCODER_PIN_A 3
#define RIGHT_ENCODER_PIN_B 4


// Wheel diameter in cm
#define WHEEL_DIAMETER (double) 10.16

// Drivetrain diameter in cm
#define DRIVETRAIN_DIAMETER (double) 20.32

/**
 * Main class for the robot. Implemented as a signleton. All important pins are defined above.
 */
class Robot {

public:
    /**
     * Singleton Constructor
     * @return A singleton Robot instance.
     */
    static Robot* instance() {
        static Robot* instance = new Robot();
        return instance;
    }

    /**
     * Destructor
     */
    ~Robot();

    /**
     * Starts the robot.
     */
    void run();

    /* Redefine these methods to prevent copies */
    Robot(Robot const&) = delete;
    void operator=(Robot const&) = delete;

private:
    Robot();

    /* Hardware Adapters */
    MotorAdapter* leftMotorAdapter;
    MotorAdapter* rightMotorAdapter;
    EncoderAdapter* leftEncoderAdapter;
    EncoderAdapter* rightEncoderAdapter;

    /* Sensors */
    EncoderSensor* leftEncoderSensor;
    EncoderSensor* rightEncoderSensor;

    /* Adafruit PWM driver */
    AdafruitPWMServoHat* pwmServoHat;

    /* Sensor manager */
    ISensorManager* sensorManager;

    /* Communicator */
    Communicator* communicator;

    /* Command Manager */
    CommandManager* commander;

};
