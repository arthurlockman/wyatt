FILE(GLOB TESTSOURCES ./*.cpp)
FILE(GLOB CXXSOURCES ../src/*.cpp)
list(REMOVE_ITEM CXXSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src/Main.cpp)
FILE(GLOB CXXCOMMANDS ../src/commands/*.cpp)
add_executable(wyatt_test ${TESTSOURCES} ${CXXSOURCES} ${CXXCOMMANDS})
target_link_libraries(wyatt_test Catch)

enable_testing()
add_test(NAME Wyatt_Testing COMMAND wyatt_test)
