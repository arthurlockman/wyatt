FILE(GLOB CXXSOURCES *.cpp)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
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
