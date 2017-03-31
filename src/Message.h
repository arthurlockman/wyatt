#pragma once

#include <string>
#include <cstdint.h>

class message {

public:
    message(string msg);
    string write();

private:
    string msg;

}