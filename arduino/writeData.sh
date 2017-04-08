#!/bin/bash
# Use:  Command     SerialFile  Address Messages
# Use:  ./writeData /dev/tty    00      01 7f FF

STR=""
for i in ${@:2}
do
        STR="$STR\x$i"
done
echo -en $STR > $1
