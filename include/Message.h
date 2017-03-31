#pragma once

#include <string>
#include <cstdint>

using namespace std;

class Message {

public:
    Message(string msg);
    string write();

private:
    string msg;

};