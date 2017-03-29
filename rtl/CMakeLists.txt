cmake_minimum_required(VERSION 3.0.0)

if (NOT BDS_ROOT)
  set(BDS_ROOT "$ENV{BDS}")
endif()
if (NOT BDS_ROOT)
  set(BDS_ROOT "C:/Program Files (x86)/Embarcadero/Studio/18.0")
  message(WARNING "Defaulting to ${BDS_ROOT}, consider running rsvars.bat or assign BDS environment variable.")
endif()
if (NOT BDSINCLUDE)
  set(BDSINCLUDE "${BDS_ROOT}/include")
endif()

# TODO: I'd prefer to be able to access these variables in the project scope, maybe assign them as property to boost?
if (CG_BOOST_ROOT)
	set(BOOST_ROOT "${CG_BOOST_ROOT}")
else()
	set(BOOST_ROOT "$ENV{CG_BOOST_ROOT}")
endif()
if (NOT BOOST_ROOT)
	set(BOOST_ROOT "${BDSINCLUDE}/boost_1_39")
endif()

if (NOT BOOST_REDIST_ROOT)
	set(BOOST_REDIST_ROOT "${BDS_ROOT}/Redist/boost/win32")
endif()

add_library(boost INTERFACE)
target_compile_options(boost INTERFACE -I\"${BOOST_ROOT}\")

add_library(boost_tr1 INTERFACE)
target_link_libraries(boost_tr1 INTERFACE boost)
target_compile_options(boost_tr1 INTERFACE -I\"${BOOST_ROOT}/boost/tr1/tr1\")
