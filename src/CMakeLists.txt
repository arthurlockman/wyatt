FILE(GLOB CXXSOURCES *.cpp)

CheckHasModule(WiringPi)

if(HAS_MODULE_WiringPi)
    add_executable(wyatt
            ${CXXSOURCES})
    message(STATUS ">>> Linux, assuming Raspberry Pi")
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
            ${CXXSOURCES}
            ../wiringPiMock/wiringPi.h
            ../wiringPiMock/wiringPi.cpp)
    message(STATUS ">>> Not linux, assuming Mac/PC")
    # Use mocked WiringPi
endif()
find_package(Threads REQUIRED)
target_link_libraries(wyatt ${CMAKE_THREAD_LIBS_INIT})
