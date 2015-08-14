# Install script for directory: /home/midgard/Dropbox/project/Strat3/strat3

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/DataManager/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/Portfolio/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/Strategy/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/DataLog/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/Report/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/test/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/Predictor/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/Error/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/Security/cmake_install.cmake")
  include("/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/cml/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "/home/midgard/Dropbox/project/Strat3/build-strat3-Desktop-Default/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()
