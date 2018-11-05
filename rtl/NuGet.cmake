cmake_minimum_required(VERSION 3.0.0)

function(download_nuget)
  message(STATUS "downloading nuget")
  file(DOWNLOAD https://dist.nuget.org/win-x86-commandline/latest/nuget.exe ${CMAKE_BINARY_DIR}/nuget.exe)
endfunction(download_nuget)

function(ensure_nuget_program)
  find_program(nuget_program NAMES nuget)
  if(${nuget_program} STREQUAL "nuget_program-NOTFOUND")
    download_nuget()
    find_program(nuget_program NAMES nuget)
  endif()
endfunction(ensure_nuget_program)

function(ensure_nuget_packagedir)
  if ("${nuget_packagedir}" STREQUAL "")
    ensure_nuget_program()
    execute_process(COMMAND ${nuget_program} locals global-packages -list RESULT_VARIABLE _gbl_result OUTPUT_VARIABLE _gbl_packagedir ERROR_VARIABLE _gbl_packagedir)
    string(STRIP "${_gbl_packagedir}" _gbl_packagedir)
    if (NOT "${_gbl_packagedir}" MATCHES "global-packages")
      message(FATAL_ERROR "Could not determine nuget global packages directory")
    endif()
    string(REGEX REPLACE "global-packages: (.*)" "\\1" _gbl_packagedir "${_gbl_packagedir}")
    string(REGEX REPLACE "\\\\$" "" _gbl_packagedir "${_gbl_packagedir}")
    string(REPLACE "\\" "/" _gbl_packagedir "${_gbl_packagedir}")
    set(nuget_packagedir "${_gbl_packagedir}" CACHE PATH "Global NuGet package directory.")
  endif()
endfunction(ensure_nuget_packagedir)

function(parse_additional_args)
  cmake_parse_arguments(package "" "SOURCE" "" ${ARGN})
  if(NOT "${package_SOURCE}" STREQUAL "")
    set(additional_args -source ${package_SOURCE} PARENT_SCOPE)
  endif()
endfunction(parse_additional_args)

function(install_nuget_package package_name package_version)
  ensure_nuget_program()
  ensure_nuget_packagedir()
  parse_additional_args(${ARGN})
  # Use a temp project.json so we can restore them to the global package folder instead of a local one.
  set(nuget_temp_dir "${CMAKE_BINARY_DIR}/_nuget_temp")
  file(WRITE "${nuget_temp_dir}/project.json" "{ \"dependencies\": { \"${package_name}\": \"${package_version}\" }, \"frameworks\": { \"native\": {} } }")
  file(WRITE "${nuget_temp_dir}/project.vcxproj" "<Project><Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" /><Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" /><Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" /></Project>")
  execute_process(COMMAND ${nuget_program} restore "${nuget_temp_dir}/project.vcxproj" ${additional_args})
  # Delete the temp stuff again.
  file(REMOVE_RECURSE "${nuget_temp_dir}")
endfunction(install_nuget_package)

function(ensure_nuget_package package_name package_version)
  ensure_nuget_packagedir()
  set(expected_package_dir ${nuget_packagedir}/${package_name}/${package_version})
  if(EXISTS "${expected_package_dir}")
    message(STATUS "Existing ${package_name} v${package_version} found in nuget package dir.")
  else()
    message(STATUS "Installing ${package_name} v${package_version}")
    install_nuget_package(${ARGV})
  endif()
  set(${package_name}_PACKAGE_DIR ${expected_package_dir} CACHE PATH "${package_name} v${package_version} package directory." FORCE)
endfunction(ensure_nuget_package)