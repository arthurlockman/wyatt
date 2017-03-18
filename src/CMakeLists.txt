add_executable(wyatt
	main.cpp
	)

# Locate wiringPi libraries
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS})

# Link against libraries
target_link_libraries(wyatt ${WIRINGPI_LIBRARIES}) 
target_link_libraries(wyatt ${CMAKE_THREAD_LIBS_INIT})
