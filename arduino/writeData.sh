#!/bin/bash
STR="\x$1\x$2"
echo $STR
echo -en $STR > /dev/cu.wchusbserial1420
