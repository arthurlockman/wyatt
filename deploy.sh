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

echo "Starting robot."

./build/src/wyatt

