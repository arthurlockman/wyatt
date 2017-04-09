#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Requires 1 arg: SerialPort"
else
    xxd -p $1
fi



