cmake_minimum_required(VERSION 3.0.0)

if (BORLAND)

  include(Borland.cmake)

  add_library(boost INTERFACE)
  if (BORLAND)
    target_compile_options(boost INTERFACE "-I\"${BOOST_ROOT}\"")
  else()
    target_include_directories(boost SYSTEM INTERFACE "${BOOST_ROOT}")
  endif()
  target_compile_definitions(boost INTERFACE BOOST_USE_WINDOWS_H INTERFACE BOOST_THREAD_USE_LIB)
  
  add_library(boost_tr1 INTERFACE)
  target_link_libraries(boost_tr1 INTERFACE boost)
  if (BORLAND)
    target_compile_options(boost_tr1 INTERFACE "-I\"${BOOST_ROOT}/boost/tr1/tr1\"")
  else()
    target_include_directories(boost_tr1 SYSTEM INTERFACE "${BOOST_ROOT}/boost/tr1/tr1")
  endif()

endif()