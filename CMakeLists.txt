cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

project(Wyatt)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/include
	)

add_subdirectory(src)

# Includes Catch in the project:
add_subdirectory(catch)
include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
enable_testing(true)  # Enables unit-testing.
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_subdirectory(test)