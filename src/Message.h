#pragma once

#include <string>
#include <cstdint>

class message {

public:
    message(string msg);
    string write();

private:
    string msg;

}