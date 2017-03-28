cmake_minimum_required(VERSION 2.6)

project(Benchmarks)
include_directories(../../include ../../hayai/src)

if(BORLAND)
  add_compile_options(-q -y -v -6 -Q)
  link_libraries(-lv -ls -lq)
  if (CG_BOOST_ROOT)
    set(BOOST_ROOT "${CG_BOOST_ROOT}")
  else()
    set(BOOST_ROOT "$ENV{CG_BOOST_ROOT}")
  endif()
  # manually add "SYSTEM" include directory to prevent make from checking all headers before compiling
  add_compile_options(-I\"${BOOST_ROOT}\")
  add_compile_options(-I\"${BOOST_ROOT}/boost/tr1/tr1\")
endif()
if(MSVC)
  #add_compile_options(/std:c++14)
endif()

file(GLOB BENCHMARK_SOURCES ./*.cpp)

add_executable(BenchmarkSuite ${BENCHMARK_SOURCES})
target_link_libraries(BenchmarkSuite hayai_main)
add_dependencies(BenchmarkSuite hayai_main)