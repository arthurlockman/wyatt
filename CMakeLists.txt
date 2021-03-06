cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS ON) #...without compiler extensions like gnu++11

project(Wyatt)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# The project version number.
set(VERSION_MAJOR   1   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

function(CheckHasModule Module)
  find_package(${Module} QUIET)
  if(NOT DEFINED ${Module}_DIR)
    set(HAS_MODULE_${Module} TRUE PARENT_SCOPE)
  elseif(${Module}_DIR)
    set(HAS_MODULE_${Module} TRUE PARENT_SCOPE)
  else()
    set(HAS_MODULE_${Module} FALSE PARENT_SCOPE)
  endif()
endfunction()

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/commands
    ${CMAKE_CURRENT_LIST_DIR}/test/mocks/include
	)

add_subdirectory(src)

# Includes Catch in the project:
add_subdirectory(catch)
include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
enable_testing(true)  # Enables unit-testing.
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_subdirectory(test)

add_subdirectory(docs)
