FILE(GLOB TESTSOURCES ./*.cpp)
FILE(GLOB CXXSOURCES ../src/*.cpp)
FILE(GLOB MOCKSRC ../wiringPiMock/*.cpp)
FILE(GLOB MOCKH ../wiringPiMock/*.h)
list(REMOVE_ITEM CXXSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src/Main.cpp)
FILE(GLOB CXXCOMMANDS ../src/commands/*.cpp)
FILE(GLOB CXXMOCKS ./mocks/*.cpp)
FILE(GLOB CXXMESSAGES ../src/messages/*.cpp)
FILE(GLOB CXXHARDWARE ../src/hardwareinterface/*.cpp)
FILE(GLOB CXXSENSORS ../src/sensors/*.cpp)

add_library(catch_main catch_main.cpp)

CheckHasModule(WiringPi)
if(HAS_MODULE_WiringPi)
    add_executable(wyatt_test
            ${TESTSOURCES}
            ${CXXSOURCES}
            ${CXXCOMMANDS}
            ${CXXMOCKS}
            ${CXXMESSAGES}
            ${CXXHARDWARE}
            ${CXXSENSORS})
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
            ${CXXMOCKS}
            ${MOCKSRC}
            ${MOCKH}
            ${CXXMESSAGES}
            ${CXXHARDWARE}
            ${CXXSENSORS})
    message(STATUS ">>> Building on Mac/PC/Linux")
endif()

message(STATUS ">>> Enabling code coverage")
include(CodeCoverage)
setup_target_for_coverage(${PROJECT_NAME}_coverage wyatt_test coverage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")

find_package(Threads REQUIRED)
target_link_libraries(catch_main Catch)
target_link_libraries(wyatt_test Catch)
target_link_libraries(wyatt_test catch_main)
target_link_libraries(wyatt_test ${CMAKE_THREAD_LIBS_INIT})

enable_testing()
add_test(NAME Wyatt_Testing COMMAND wyatt_test)
