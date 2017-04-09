#pragma once

class DuplicateHardwareException: public std::exception {

    public:
        DuplicateHardwareException(Hardware hardware) : std::exception() {
            this->hardware = hardware;
        }

        virtual const char* what() const throw() {
            std::string msg("Hardware has already been added. Address: ");
            msg.push_back((this->hardware).address);
            return msg.c_str();
        }

    private:
        Hardware hardware;
};

class NonexistentHardwareException: public std::exception {

    public:
        NonexistentHardwareException(Hardware hardware) : std::exception() {
            this->hardware = hardware;
        }

        virtual const char* what() const throw() {
            std::string msg("Hardware does not exist. Address: ");
            msg.push_back((this->hardware).address);
            return msg.c_str();
        }

    private:
        Hardware hardware;
};
