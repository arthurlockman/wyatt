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
make
cd ..
if [ -e /dev/ttyUSB0 ]; then
    echo "Deploying to Arduino..."
    rm ./Arduino/Hardware.cpp
    rm ./Arduino/Hardware.h
    cp ./src/Hardware.cpp ./Arduino/Hardware.cpp
    cp ./src/Hardware.h ./Arduino/Hardware.h
    /usr/local/arduino-1.8.2/arduino --board arduino:avr:nano:cpu=atmega328 --port /dev/ttyUSB0 --upload ./arduino/serialTest/serialTest.ino
else
    echo "No Arduino connected."
fi
./build/src/wyatt

