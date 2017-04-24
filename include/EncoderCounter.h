#pragma once

#include "Thread.h"
#include "IHardwareInterface.h"
#include "Message.h"
#include <atomic>
#include <list>
#include <chrono>
#include "wiringPiInclude.h"
#include <stdlib.h>

class EncoderCounter : public Thread, public IHardwareInterface
{
public:
    /**
     * Counts a two-channel encoder.
     *
     * @param channelA WiringPi Pin for channel A.
     * @param channelB WiringPi Pin for channel B.
     * @param ticksPerRev Number of ticks per revolution on this encoder.
     */
    EncoderCounter(int channelA, int channelB, int ticksPerRev);
    /**
     * Destructs the encoder counter.
     */
    ~EncoderCounter();
    /**
     * Runs the encoder counter worker thread.
     * @return nothing
     */
    void* run();
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
    std::list<Message*>* read();
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
    std::atomic<double> m_speed;
    //! Current encoder count.
    std::atomic<long> m_count;
};
