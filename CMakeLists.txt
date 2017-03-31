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

