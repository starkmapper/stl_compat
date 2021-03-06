cmake_minimum_required(VERSION 3.0.0)

include(./NuGet.cmake)

# TODO: Use a generator to download the required packages and add *.nuget.targets.

# Set specific boost version otherwise we wouldn't have a consistent version when building.
if (MSVC)
  set(boost_version "1.65.1" CACHE INTERNAL "")
endif()

function(install_boost_lib lib_name)
  # Set the last digit to 0 so that we don't need to check against 1910 1911 1912 individually.
  math(EXPR MSVC_VERSION_SHORT "${MSVC_VERSION} - (${MSVC_VERSION} % 10)")

  set(package_version ${boost_version})

  ensure_nuget_packagedir()

  if(${MSVC})
    if(${MSVC_VERSION_SHORT} EQUAL 1200)
      set(msvc_lib_version  60)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1300)
      set(msvc_lib_version  70)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1310)
      set(msvc_lib_version  71)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1400)
      set(msvc_lib_version  80)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1500)
      set(msvc_lib_version  90)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1600)
      set(msvc_lib_version 100)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1700)
      set(msvc_lib_version 110)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1800)
      set(msvc_lib_version 120)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1900)
      set(msvc_lib_version 140)
    elseif(${MSVC_VERSION_SHORT} EQUAL 1910)
      set(msvc_lib_version 141)
    else()
      message(FATAL_ERROR "MSVC version ${MSVC_VERSION} not known")
    endif()
    set(msvc_lib_version_string "-vc${msvc_lib_version}")
  endif()
  set(boost_lib_name "boost_${lib_name}")
  set(package_name "${boost_lib_name}${msvc_lib_version_string}")
  ensure_nuget_package(${package_name} ${package_version})

  set(package_dir ${${package_name}_PACKAGE_DIR})
  add_library(${boost_lib_name} INTERFACE)
  target_link_libraries(${boost_lib_name} INTERFACE boost)
  target_link_libraries(boost_libs INTERFACE ${boost_lib_name})
  #check for 32_bits
  if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(bits "32")
  else()
    set(bits "64")
  endif()
  file(TO_NATIVE_PATH "${package_dir}/lib/native/address-model-${bits}/lib" lib_link_path)
  message(STATUS "Adding boost lib include path ${lib_link_path}")
  target_link_libraries(${boost_lib_name} INTERFACE "-LIBPATH:${lib_link_path}")
endfunction(install_boost_lib lib_name)

if (BORLAND)
  include(Borland.cmake)
endif()
add_library(boost_tr1 INTERFACE)
add_library(boost INTERFACE)
add_library(boost_libs INTERFACE)
if(MSVC AND NOT BOOST_ROOT)
  ensure_nuget_package("Boost" ${boost_version})
  set(BOOST_ROOT ${Boost_PACKAGE_DIR}/lib/native/include CACHE PATH "Boost root.")
endif()

if(BOOST_ROOT)
  message(STATUS "Using boost directory: ${BOOST_ROOT}")

  target_include_directories(boost SYSTEM INTERFACE "${BOOST_ROOT}")
  target_compile_definitions(boost INTERFACE BOOST_USE_WINDOWS_H INTERFACE BOOST_THREAD_USE_LIB)
  #target_compile_definitions(boost INTERFACE BBOOST_ASIO_ENABLE_HANDLER_TRACKING)

  target_link_libraries(boost_tr1 INTERFACE boost)
  target_include_directories(boost_tr1 SYSTEM INTERFACE "${BOOST_ROOT}/boost/tr1/tr1")
else()
  message(WARNING "No boost configured, only native features supported")
endif()

if(MSVC)
  install_boost_lib(system)
  install_boost_lib(date_time)
  install_boost_lib(regex)
  install_boost_lib(filesystem)
endif()