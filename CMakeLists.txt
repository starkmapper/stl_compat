cmake_minimum_required(VERSION 3.0.0)

project(stl_compat)
SET(CMAKE_BUILD_TYPE Release)

add_subdirectory(rtl)

add_library(stl_compat INTERFACE)
target_include_directories(stl_compat INTERFACE include)
if(BORLAND)
	target_link_libraries(stl_compat INTERFACE boost)
endif()

if(NOT TARGET hayai_main)
	add_subdirectory(hayai)
endif()
add_subdirectory(example)
add_subdirectory(test)
