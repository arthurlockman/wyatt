#include "EncoderAdapter.h"
#include <iostream>

EncoderAdapter::EncoderAdapter(int channelA, int channelB, int ticksPerRev, Hardware hardware):
    m_channelA(channelA),
    m_channelB(channelB),
    m_count(0),
    m_lastTransition(-2),
    m_ticksPerRevolution(ticksPerRev),
    hardware(hardware)
{
    m_revolutionsPerTick = 10.0 / (double)ticksPerRev;
    pinMode(channelA, INPUT);
    pinMode(channelB, INPUT);
    m_channelAState = digitalRead(m_channelA);
    m_channelBState = digitalRead(m_channelB);
}

EncoderAdapter::~EncoderAdapter()
{

}

void* EncoderAdapter::run()
{
    int numTicks = 0;
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
        numTicks += abs(newTransition);
        if (numTicks >= 10)
        {
            numTicks = 0;
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

long EncoderAdapter::getCount()
{
    return m_count;
}

void EncoderAdapter::resetCount()
{
    this->signal(1);
}

std::list<IMessage*>* EncoderAdapter::read()
{
    std::list<IMessage*>* messages = new std::list<IMessage*>();
    IMessage* msg = new EncoderMessage(this->hardware, this->m_speed);
    messages->push_back(msg);

    return messages;
}

double EncoderAdapter::getSpeedRPM()
{
    return m_speed;
}
