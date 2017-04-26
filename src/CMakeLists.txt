FILE(GLOB CXXSOURCES *.cpp)
FILE(GLOB CXXMESSAGES ./messages/*.cpp)
FILE(GLOB CXXCOMMANDS ./commands/*.cpp)
FILE(GLOB MOCKSRC ../wiringPiMock/*.cpp)
FILE(GLOB MOCKH ../wiringPiMock/*.h)
FILE(GLOB CXXMESSAGES ../src/messages/*.cpp)
FILE(GLOB CXXHARDWARE ./hardwareinterface/*.cpp)
FILE(GLOB CXXSENSORS ./sensors/*.cpp)

CheckHasModule(WiringPi)

if(HAS_MODULE_WiringPi)
    add_executable(wyatt
            ${CXXSOURCES}
            ${CXXCOMMANDS}
            ${CXXMESSAGES}
            ${CXXHARDWARE}
            ${CXXSENSORS})
    message(STATUS ">>> Building on Raspberry Pi")
    # Use real WiringPi
    # Locate wiringPi libraries
    find_package(WiringPi REQUIRED)

    # Include headers
    include_directories(${WIRINGPI_INCLUDE_DIRS})

    # Link against libraries
    target_link_libraries(wyatt ${WIRINGPI_LIBRARIES})
    target_compile_definitions(wyatt PRIVATE IS_RASPI=1)
else()
    add_executable(wyatt
            ${TESTSOURCES}
            ${CXXSOURCES}
            ${MOCKSRC}
            ${MOCKH}
            ${CXXCOMMANDS}
            ${CXXMESSAGES}
            ${CXXHARDWARE}
            ${CXXSENSORS})
    message(STATUS ">>> Building on Mac/PC/Linux")
    # Use mocked WiringPi
endif()
find_package(Threads REQUIRED)
target_link_libraries(wyatt ${CMAKE_THREAD_LIBS_INIT})
