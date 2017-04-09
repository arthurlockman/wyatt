//
// Created by Arthur Lockman on 4/9/17.
//

#ifndef WYATT_COMMUNICATIONEXCEPTION_H
#define WYATT_COMMUNICATIONEXCEPTION_H

class CommunicationException: public exception
{
    virtual const char* what() const throw()
    {
        return "An exception has occurred in our communication thread.";
    }
};

#endif //WYATT_COMMUNICATIONEXCEPTION_H
