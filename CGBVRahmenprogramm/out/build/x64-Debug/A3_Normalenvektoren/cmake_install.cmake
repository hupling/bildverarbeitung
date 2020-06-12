# Install script for directory: D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/A3_Normalenvektoren

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
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/A3_Normalenvektoren" TYPE EXECUTABLE FILES "D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/A3_Normalenvektoren/A3_Normalenvektoren.exe")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/A3_Normalenvektoren" TYPE EXECUTABLE FILES "D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/out/build/x64-Debug/A3_Normalenvektoren/A3_Normalenvektoren.exe")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xA3_Normalenvektorenx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/A3_Normalenvektoren" TYPE FILE FILES
    "D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/A3_Normalenvektoren/Aufgabe3.cpp"
    "D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/A3_Normalenvektoren/VertexShader.glsl"
    "D:/EigeneDateien/Documents/Uni/6.Semester/Bildverarbeitung/repo/CGBVRahmenprogramm/A3_Normalenvektoren/FragmentShader.glsl"
    )
endif()

