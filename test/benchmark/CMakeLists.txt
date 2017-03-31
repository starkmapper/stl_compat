cmake_minimum_required(VERSION 2.6)

include_directories(../../hayai/src)

if(BORLAND)
  add_compile_options(-q -y -6 -Q)
  link_libraries(-lv -ls -lq)
endif()
if(MSVC)
  #add_compile_options(/std:c++14)
endif()

file(GLOB BENCHMARK_SOURCES ./*.cpp)

add_executable(BenchmarkSuite ${BENCHMARK_SOURCES})
target_link_libraries(BenchmarkSuite stl_compat hayai_main)

add_test(NAME BenchmarkSuite COMMAND BenchmarkSuite --output junit:BenchmarkSuite.results.xml)