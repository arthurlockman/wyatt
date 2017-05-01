//
// Created by Tucker Haydon on 4/26/17.
//

#pragma once

/**
 * Custom exception thrown when some data exceeds normal bounds (ex: motor speed)
 */
class DataSizeException: public std::exception {

public:
    /**
     * Constructor
     * @param data An integer piece of data
     */
    DataSizeException(int data) : std::exception() {
        this->data = data;
    }

    /**
     * Returns a message describing what went wrong.
     * @return A char pointer to a message of what went wrong.
     */
    virtual const char* what() const throw() {
        std::string msg("Data is too large or small. Data: ");
        msg += this->data;
        return msg.c_str();
    }

private:
    int data;
};