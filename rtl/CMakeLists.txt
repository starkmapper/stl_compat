cmake_minimum_required(VERSION 3.0.0)

include(Borland.cmake)

if (BORLAND)

	add_library(boost INTERFACE)
	target_compile_options(boost INTERFACE -I\"${BOOST_ROOT}\")
	target_compile_options(boost INTERFACE -DBOOST_ALL_NO_LIB)

	add_library(boost_tr1 INTERFACE)
	target_link_libraries(boost_tr1 INTERFACE boost)
	target_compile_options(boost_tr1 INTERFACE -I\"${BOOST_ROOT}/boost/tr1/tr1\")

	file(GLOB_RECURSE BOOST_THREAD_SOURCES "${BOOST_ROOT}/libs/thread/src/win32/*" "${BOOST_ROOT}/libs/thread/src/tss_null.cpp")
	add_library(boost_thread STATIC ${BOOST_THREAD_SOURCES})
	target_link_libraries(boost_thread PUBLIC boost)
	target_compile_options(boost_thread PRIVATE -I\"${BOOST_ROOT}\" -DBOOST_THREAD_BUILD_LIB)
	target_compile_options(boost_thread INTERFACE -I\"${BOOST_ROOT}\" -DBOOST_THREAD_USE_LIB)

endif()