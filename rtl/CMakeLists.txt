cmake_minimum_required(VERSION 3.0.0)

include(Borland.cmake)

if (BORLAND)

	add_library(boost INTERFACE)
	target_compile_options(boost INTERFACE -I\"${BOOST_ROOT}\")

	add_library(boost_tr1 INTERFACE)
	target_link_libraries(boost_tr1 INTERFACE boost)
	target_compile_options(boost_tr1 INTERFACE -I\"${BOOST_ROOT}/boost/tr1/tr1\")

endif()