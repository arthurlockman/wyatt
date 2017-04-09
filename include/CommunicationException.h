//
// Created by Arthur Lockman on 4/9/17.
//

#pragma once


// This is a general example of an exception, please don't ever actually throw it.
class CommunicationException: public exception
{
    virtual const char* what() const throw()
    {
        return "An exception has occurred in our communication thread.";
    }
};

class ArduinoMappingException: public exception
{
    virtual const char* what() const throw()
    {
	return "The comm port you're attemping to attach an arduino to already has hardware associated!";
    }
};

class EmptyMessageQueueException : public exception
{
    virtual const char* what() const throw()
    {
	return "The message quque you're attempting to retreive a message from is empty!";
    }
};

class MessageHasNoQueueException : public exception
{
    virtual const char* what() const throw()
    {
	return "A message was attempted to be enqueued, but the hardware associated with the message does not have a queue!";
    }
};
