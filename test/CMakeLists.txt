FILE(GLOB TESTSOURCES ./*.cpp)
FILE(GLOB CXXSOURCES ../src/*.cpp)
list(REMOVE_ITEM CXXSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src/Main.cpp)
FILE(GLOB CXXCOMMANDS ../src/commands/*.cpp)


CheckHasModule(WiringPi)
if(HAS_MODULE_WiringPi)
    add_executable(wyatt_test ${TESTSOURCES} ${CXXSOURCES} ${CXXCOMMANDS})
    # Use real WiringPi
    # Locate wiringPi libraries
    find_package(WiringPi REQUIRED)
    # Include headers
    include_directories(${WIRINGPI_INCLUDE_DIRS})
    # Link against libraries
    target_link_libraries(wyatt_test ${WIRINGPI_LIBRARIES})
    target_compile_definitions(wyatt_test PRIVATE IS_RASPI=1)
    message(STATUS ">>> Building on Raspberry Pi")
else()
    add_executable(wyatt_test 
        ${TESTSOURCES} 
        ${CXXSOURCES} 
        ${CXXCOMMANDS} 
        ../wiringPiMock/wiringPi.h 
        ../wiringPiMock/wiringPi.cpp
        ../wiringPiMock/wiringSerial.h
        ../wiringPiMock/wiringSerial.cpp)
    message(STATUS ">>> Building on Mac/PC/Linux")
endif()

find_package(Threads REQUIRED)
target_link_libraries(wyatt_test Catch)
target_link_libraries(wyatt_test ${CMAKE_THREAD_LIBS_INIT})

enable_testing()
add_test(NAME Wyatt_Testing COMMAND wyatt_test)
