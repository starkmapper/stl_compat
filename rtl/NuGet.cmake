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
  set(nuget_program "${nuget_program}" PARENT_SCOPE)
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
    set(nuget_packagedir "${_gbl_packagedir}" PARENT_SCOPE)
  endif()
endfunction(ensure_nuget_packagedir)

function(install_nuget_package package_name package_version)
  ensure_nuget_program()
  ensure_nuget_packagedir()
  # Use a temp project.json so we can restore them to the global package folder instead of a local one.
  set(nuget_temp_dir "${CMAKE_BINARY_DIR}/_nuget_temp")
  file(WRITE "${nuget_temp_dir}/project.json" "{ \"dependencies\": { \"${package_name}\": \"${package_version}\" }, \"frameworks\": { \"native\": {} } }")
  file(WRITE "${nuget_temp_dir}/project.vcxproj" "<Project><Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" /><Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" /><Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" /></Project>")
  execute_process(COMMAND ${nuget_program} restore "${nuget_temp_dir}/project.vcxproj")
  # Delete the temp stuff again.
  file(REMOVE_RECURSE "${nuget_temp_dir}")
endfunction(install_nuget_package)