while test $# != 0
do
    case "$1" in
        -c|--clean) rm -rf build ;;
    esac
    shift
done


if [ ! -d "./build" ]; then
    mkdir build
fi
cd build
cmake ..
make -j$(($(getconf _NPROCESSORS_ONLN) + 1))
cd ..
if [ -e /dev/ttyUSB0 ]; then
    echo "Deploying to Arduino..."
    rm ./Arduino/Hardware.cpp
    rm ./Arduino/Hardware.h
    cp ./src/Hardware.cpp ./Arduino/Hardware.cpp
    cp ./include/Hardware.h ./Arduino/Hardware.h
    /usr/local/arduino-1.8.2/arduino --board arduino:avr:nano:cpu=atmega328 --port /dev/ttyUSB0 --upload ./Arduino/Arduino.ino
else
    echo "No Arduino connected."
fi

echo "Starting robot."

./build/src/wyatt

