#pragma once

class MotorController {
public:
    /**
     * Construct the motor controller. This needs to be overridden
     * in subclasses to provide specific functionality.
     */
    MotorController();
    /**
     * Destroy this motor controller object.
     */
    virtual ~MotorController() = 0;
    /**
     * Set a certain motor on the motor controller to a given 
     * speed. This needs to be overridden in subclasses to
     * provide specific functionality for a specific type of motor
     * controller.
     *
     * @param motorID The ID of the motor on the controller bus.
     * @param speed The speed to set the motor to.
     *
     * @return A bool, true if successful.
     */
    bool setMotor(int motorID, int speed);
    /**
     * Stop a motor (set speed to 0).
     *
     * @param motorID The motor to stop.
     *
     * @return A bool, true if successful.
     */
    bool stopMotor(int motorID);
    /**
     * Stop all motors driven by this controller.
     *
     * @return A bool, true if successful.
     */
    bool stopAllMotors();
};

