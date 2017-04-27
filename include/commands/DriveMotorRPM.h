//
// Created by Tucker Haydon on 4/27/17.
//

#pragma once
#include "../hardwareinterface/MotorAdapter.h"
#include "../sensors/EncoderSensor.h"
#include "../Communicator.h"
#include "Command.h"
#include "../DriveConstants.h"
#include <stdlib.h>
#include <math.h>

/**
 * Command object used to drive a motor at a specified RPM. Uses a PD controller to maintain speed.
 */
class DriveMotorRPM: public Command {

public:

    /**
     * Constructor.
     * @param comm A communicator object to dispatch motor messages to
     * @param motorHardware The hardware object associated with the motor.
     * @param encoder The encoder sensor maintaining the most recent encoder readings
     * @param desiredRPM The desired RPM
     * @param direction The direction to drive the motor. Specified in DriveConstants. FORWARD=1, BACKWARD=-1
     */
    DriveMotorRPM(Communicator* comm, Hardware motorHardware, EncoderSensor* encoder, int desiredRPM, int direction);

    /**
     * Destructor
     */
    ~DriveMotorRPM();

    /**
     * This function gets periodically run by the CommandManger. PD control is executed. Always returns true, ensure that control is always executing.
     * @return True.
     */
    bool execute() override;

    /**
     * Cleanup. Currently does nothing.
     * @param canceled
     * @return True
     */
    bool cleanup(bool canceled) override;

private:
    int desiredRPM;
    int direction;
    Hardware motorHardware;
    EncoderSensor* encoder;
    Communicator* comm;

    double k_p = 5.0;
    double k_d = 1.0;

    double lastDiff = 0;

};