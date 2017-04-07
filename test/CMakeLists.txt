FILE(GLOB CXXSOURCES *.cpp)
add_executable(wyatt_test ${CXXSOURCES})
target_link_libraries(wyatt_test Catch)

enable_testing()
add_test(NAME Wyatt_Testing COMMAND wyatt_test)
