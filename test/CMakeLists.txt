cmake_minimum_required(VERSION 2.6)

if(TARGET tdog)
# Stl UnitTests Suite
set(TEST_TARGET StlUnitTestSuite)
file(GLOB_RECURSE UNITTEST_SOURCES StlUnitTests/*.cpp StlUnitTests/*.h)
message(STATUS "UnitTestSources: ${UNITTEST_SOURCES}")
add_executable(${TEST_TARGET} ${UNITTEST_SOURCES})
target_options(${TEST_TARGET})
target_compile_definitions(${TEST_TARGET} PRIVATE "TEST_TARGET=${TEST_TARGET}")
target_link_libraries(${TEST_TARGET} PUBLIC tdog PUBLIC stl_compat)

add_test(NAME ${TEST_TARGET}
         COMMAND $<TARGET_FILE:${TEST_TARGET}> WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

# Stl Benchmark Suite
set(TEST_TARGET StlBenchmarkSuite)
file(GLOB_RECURSE BENCHMARK_SOURCES StlBenchmarks/*.cpp StlBenchmarks/*.h)
add_executable(${TEST_TARGET} ${BENCHMARK_SOURCES})
target_options(${TEST_TARGET})
target_compile_definitions(${TEST_TARGET} PRIVATE "TEST_TARGET=${TEST_TARGET}")
target_include_directories(${TEST_TARGET} PUBLIC ../hayai/src)
target_link_libraries(${TEST_TARGET} PUBLIC hayai_main PUBLIC stl_compat)

add_test(NAME ${TEST_TARGET}
         COMMAND $<TARGET_FILE:${TEST_TARGET}> --output junit:${TEST_TARGET}.results.xml
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
