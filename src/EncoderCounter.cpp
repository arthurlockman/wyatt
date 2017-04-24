#include "EncoderCounter.h"
#include "wiringPiInclude.h"

EncoderCounter::EncoderCounter(int channelA, int channelB, int ticksPerRev):
    m_channelA(channelA),
    m_channelB(channelB),
    m_count(0),
    m_lastTransition(-2),
    m_ticksPerRevolution(ticksPerRev)
{
    m_revolutionsPerTick = 1.0 / (double)ticksPerRev;
    pinMode(channelA, INPUT);
    pinMode(channelB, INPUT);
    m_channelAState = digitalRead(m_channelA);
    m_channelBState = digitalRead(m_channelB);
}

EncoderCounter::~EncoderCounter()
{

}

void* EncoderCounter::run()
{
    while (m_signal >= 0)
    {
        if (m_signal == 1) // Reset count
        {
            m_count = 0;
            m_signal = 0;
        }
        int newChannelAState = digitalRead(m_channelA);
        int newChannelBState = digitalRead(m_channelB);
        int newTransition = (newChannelAState != m_channelAState) ? 1 : (newChannelBState != m_channelBState) ? -1 : 0;
        // Calculate encoder speed in RPM, store in m_speed
        if (newTransition != 0)
        {
            std::chrono::high_resolution_clock::time_point newTime = std::chrono::high_resolution_clock::now();
            std::chrono::microseconds diffTime = std::chrono::duration_cast<std::chrono::microseconds>(newTime - m_lastTickTime);
            m_lastTickTime = newTime;
            m_speed = (m_revolutionsPerTick / (double)diffTime.count()) * 60000000.0;
        }
        m_channelAState = newChannelAState;
        m_channelBState = newChannelBState;
        // If last transition is uninitialized, initialize direction to whichever transition just occurred. It will
        // be forward if the A channel is read first, and backward if B is read first. Otherwise, direction
        // will be reversed if it reads two transitions from the same channel in sequence.
        m_direction = (m_lastTransition == -2) ? newTransition : (newTransition == m_lastTransition) ? -m_direction : m_direction;
        // Set last transition only if a new transition has occurred.
        m_lastTransition = (newTransition == 0) ? m_lastTransition : newTransition;
        // Add the direction (-1, 1) to the encoder count. If no transition has occurred, do nothing.
        m_count = (newTransition != 0) ? (long)m_count + m_direction : (long)m_count;
    }
    return NULL;
}

long EncoderCounter::getCount()
{
    return m_count;
}

void EncoderCounter::resetCount()
{
    this->signal(1);
}

std::list<Message*>* EncoderCounter::read()
{
    // TODO: finish stub, return a list with a speed and ticks message.
    std::list<Message*>* tmpList = new std::list<Message*>();
//    Message* tmpMessage = new Message();
    return tmpList;
}

double EncoderCounter::getSpeedRPM()
{
    return m_speed;
}
