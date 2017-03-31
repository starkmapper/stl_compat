cmake_minimum_required(VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/stl_compat)

if(BORLAND)
  add_compile_options(-q -y -v -6 -Q)
  link_libraries(-lv -ls -lq)
endif()
if(MSVC)
  add_compile_options(/std:c++latest)
endif()

file(GLOB example_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ./*.cpp)
#message(STATUS "generating example projects:")
foreach(example_src ${example_sources})
  string(REPLACE ".cpp" "" example_name ${example_src})
  #message(STATUS "  Creating project ${example_name}")
  add_executable(${example_name} ${example_src})
  target_link_libraries(${example_name} PUBLIC stl_compat)
endforeach(example_src)
#optional example
