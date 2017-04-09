FILE(GLOB CXXSOURCES *.cpp)
FILE(GLOB CXXCOMMANDS ./commands/*.cpp)

CheckHasModule(WiringPi)

if(HAS_MODULE_WiringPi)
    add_executable(wyatt
            ${CXXSOURCES}
            ${CXXCOMMANDS})
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
            ${CXXCOMMANDS}
            ../wiringPiMock/wiringPi.h
            ../wiringPiMock/wiringPi.cpp
            ../wiringPiMock/wiringSerial.h
            ../wiringPiMock/wiringSerial.cpp)
    message(STATUS ">>> Building on Mac/PC/Linux")
    # Use mocked WiringPi
endif()
find_package(Threads REQUIRED)
target_link_libraries(wyatt ${CMAKE_THREAD_LIBS_INIT})
