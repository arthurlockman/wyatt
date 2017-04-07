if [! -d "./build" ]; then
    mkdir build
fi

cd build
cmake ..
make
cd ..
if [ -e /dev/ttyUSB0 ]; then
    echo "Deploying to Arduino..."
    arduino --board arduino:avr:nano:cpu=atmega328 --port /dev/ttyUSB0 --upload ./arduino/serialTest/serialTest.ino
else
    echo "No Arduino connected."
fi
./build/src/wyatt

