#pragma once

#define GEAR_RATIO ((double) 1/19.0 * 3.0/5.0)

#include "Thread.h"
#include "IHardwareInterface.h"
#include "messages/IMessage.h"
#include <atomic>
#include <list>
#include <chrono>
#include "wiringPiInclude.h"
#include <stdlib.h>
#include <string>
#include "messages/EncoderMessage.h"
#include <mutex>

/**
 * Hardware adapter for the Pololu encoders. This class polls pins on the RaspberryPi, counts the number of ticks, and translates this data into a specific RPM. Periodically, the communicator requests the current RPM of the encoders to inject it into the EncoderSensor object.
 * TODO: This class should translate the data into a specific velocity in cm/s
 */
class EncoderAdapter : public Thread, public IHardwareInterface
{
public:
    /**
     * Counts a two-channel encoder.
     *
     * @param channelA WiringPi Pin for channel A.
     * @param channelB WiringPi Pin for channel B.
     * @param ticksPerRev Number of ticks per revolution on this encoder.
     */
    EncoderAdapter(int channelA, int channelB, int ticksPerRev, Hardware hardware);
    /**
     * Destructs the encoder counter.
     */
    ~EncoderAdapter() override;
    /**
     * Runs the encoder counter worker thread.
     * @return nothing
     */
    void* run() override;
    /**
     * Get the current count from the encoder.
     * @return a long, the encoder count (+/-)
     */
    long getCount();
    /**
     * Reset the encoder count to 0.
     */
    void resetCount();
    /**
     * Get the encoder current speed in RPM.
     * @return A speed in RPM.
     */
    double getSpeedRPM();
    /**
     * Read a list containing a message with the
     * current encoder count for this encoder, and a message with the
     * current speed.
     * @return A message list object containing the count/speed for this encoder.
     */
    std::list<IMessage*>* read() override;
    void write(IMessage* message) override {};
private:
    //! Pin for the encoder A channel.
    int m_channelA;
    //! Pin for the encoder B channel.
    int m_channelB;
    //! Last state of the encoder A channel.
    int m_channelAState;
    //! Last state of the encoder B channel.
    int m_channelBState;
    //! Last transition between encoder channel states.
    int m_lastTransition;
    //! Current encoder direction.
    int m_direction;
    //! Number of ticks per revolution of the encoder.
    int m_ticksPerRevolution;
    //! Ratio of one tick to a number of revolutions.
    double m_revolutionsPerTick;
    //! Last time the encoder ticked.
    std::chrono::high_resolution_clock::time_point m_lastTickTime;
    //! Current encoder speed in RPM.
    volatile double m_speed;
    std::mutex m_lock;
    //! Current encoder count.
    std::atomic<long> m_count;
    //! The hardware for the encoder
    Hardware hardware;
};
