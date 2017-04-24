#pragma once

#include "Thread.h"
#include "IHardwareInterface.h"
#include "Message.h"
#include <atomic>
#include <list>

class EncoderCounter : public Thread, public IHardwareInterface
{
public:
    /**
     * Counts a two-channel encoder.
     *
     * @param channelA WiringPi Pin for channel A.
     * @param channelB WiringPi Pin for channel B.
     */
    EncoderCounter(int channelA, int channelB);
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
     * Read a list containing a message with the
     * current encoder count for this encoder.
     * @return A message object containing the count for this encoder.
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
    //! Current encoder count.
    std::atomic<long> m_count;
};
