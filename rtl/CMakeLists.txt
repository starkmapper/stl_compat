cmake_minimum_required(VERSION 3.0.0)

if (BORLAND)

  include(Borland.cmake)

  add_library(boost INTERFACE)
  target_include_directories(boost SYSTEM INTERFACE "${BOOST_ROOT}")
  target_compile_definitions(boost INTERFACE BOOST_THREAD_USE_LIB)

  add_library(boost_tr1 INTERFACE)
  target_link_libraries(boost_tr1 INTERFACE boost)
  target_include_directories(boost_tr1 SYSTEM INTERFACE "${BOOST_ROOT}/boost/tr1/tr1")

endif()