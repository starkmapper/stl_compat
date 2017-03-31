cmake_minimum_required(VERSION 3.0.0)

if (BORLAND)

  include(Borland.cmake)

  add_library(boost INTERFACE)
  target_compile_options(boost INTERFACE -I\"${BOOST_ROOT}\")
  target_compile_options(boost INTERFACE -DBOOST_THREAD_USE_LIB)

  add_library(boost_tr1 INTERFACE)
  target_link_libraries(boost_tr1 INTERFACE boost)
  target_compile_options(boost_tr1 INTERFACE -I\"${BOOST_ROOT}/boost/tr1/tr1\")

endif()