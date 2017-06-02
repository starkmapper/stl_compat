cmake_minimum_required(VERSION 3.0.0)

project(stl_compat)
SET(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
enable_testing()

include(./Options.cmake)

add_subdirectory(rtl)

add_library(stl_compat INTERFACE)
target_include_directories(stl_compat INTERFACE include)
if(BORLAND)
  target_link_libraries(stl_compat INTERFACE boost)
endif()

if(NOT TARGET hayai_main)
  add_subdirectory(hayai)
endif()
if(NOT TARGET tdog)
  add_subdirectory(tdog)
endif()

add_subdirectory(example)
add_subdirectory(test)
