cmake_minimum_required(VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)

add_subdirectory(benchmark)
#add_subdirectory(unit_test)

if(TARGET tdog)

# Core UnitTests Suite
file(GLOB_RECURSE UNITTEST_SOURCES StlUnitTests/*.cpp StlUnitTests/*.h)
add_executable(StlUnitTests ${UNITTEST_SOURCES})
target_orbit_options(StlUnitTests)
target_include_directories(StlUnitTests PUBLIC .)
target_link_libraries(StlUnitTests PUBLIC tdog PUBLIC stl_compat)

endif()