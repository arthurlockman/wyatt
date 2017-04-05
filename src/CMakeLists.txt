FILE(GLOB CXXSOURCES *.cpp)

add_executable(wyatt
	${CXXSOURCES}
	)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
    message(STATUS ">>> Linux, assuming Raspberry Pi")
    # Use real WiringPi
    # Locate wiringPi libraries
    find_package(WiringPi REQUIRED)

    # Include headers
    include_directories(${WIRINGPI_INCLUDE_DIRS})

    # Link against libraries
    target_link_libraries(wyatt ${WIRINGPI_LIBRARIES}) 
else()
    message(STATUS ">>> Not linux, assuming Mac/PC")
    # Use mocked WiringPi
endif()
find_package(Threads REQUIRED)
target_link_libraries(wyatt ${CMAKE_THREAD_LIBS_INIT})
