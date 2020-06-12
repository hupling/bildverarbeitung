# Install script for directory: D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/Texturen")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/Dependencies/cmake_install.cmake")
  include("D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/ImageLoader/cmake_install.cmake")
  include("D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/A1_Versuch1a/cmake_install.cmake")
  include("D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/A1_Versuch1b/cmake_install.cmake")
  include("D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/A1_Bildverarbeitung/cmake_install.cmake")
  include("D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/A3_Normalenvektoren/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
