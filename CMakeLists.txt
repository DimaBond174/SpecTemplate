# This is the source code of SpecNet project
#
#  Copyright (c) Dmitriy Bondarenko
#  feel free to contact me: specnet.messenger@gmail.com
#
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(retail_mon)

set(Proj_VERSION  "1.0")
set(Proj_SERVICE  "retail_mon_serv")

# TODO Set Clang path in Environment:
#PATH="/usr/local/clang_8.0.0/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games"
#LD_LIBRARY_PATH="/usr/local/clang_8.0.0/lib"
#CC="/usr/local/clang_8.0.0/bin/clang"
#CXX="/usr/local/clang_8.0.0/bin/clang++"
#ocv_update(CLANG_PATH "/usr/local/clang_8.0.0" CACHE PATH "Clang folder")
#message("CLANG_PATH: ${CLANG_PATH}")
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_C_COMPILER clang)


include(cmake/OpenCVUtils.cmake)
include(cmake/OpenCVModule.cmake)

# TODO if need debug CMake build to JSON:
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# TODO Set build type:
set(CMAKE_BUILD_TYPE "Debug")
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# TODO Set OpenCV path:
ocv_update(OPENCV_BUILD_PATH "/home/dbond/workspace5/git/opencv/opencv.build64" CACHE PATH "OpenCV folder")
message("OPENCV_BUILD_PATH: ${OPENCV_BUILD_PATH}")

# TODO Needto build GUI:
#option(CREATE_GUI "Create GUI exec" OFF)
set(CREATE_GUI "OFF")

# TODO Needto build Service:
#option(CREATE_SERVICE "Create Service exec" ON)
set(CREATE_SERVICE "OFF")

# TODO Needto build Tests:
#option(CREATE_SERVICE "Create Service exec" ON)
set(CREATE_TESTS "ON")

# TODO Set bin folder:
ocv_update(CUR_EXEC_FOLDER "../retail_cpp_bin" CACHE PATH "Binary output folder")
message("CUR_EXEC_FOLDER: ${CUR_EXEC_FOLDER}")
# you can set CMAKE_BINARY_DIR for temp files:
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

set(SPEC_PROPERTIES
    DEBUG_POSTFIX             "d"
)
# TODO Enshure target build is what you want:
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(SPEC_BUILD DDEBUG)
else()
    set(SPEC_BUILD DRELEASE)
endif()

# Output folder for binaries
set(SPEC_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CUR_EXEC_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPEC_BUILD_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPEC_BUILD_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPEC_BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${SPEC_BUILD_DIR})

include(cmake/functions.cmake)

set(SPEC_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common
    )

set(SPEC_SRC_COMMON
      ${CMAKE_CURRENT_SOURCE_DIR}/src/common
      )

set(SPEC_LIB_DIR
          ${CMAKE_CURRENT_SOURCE_DIR}/static
          )

  # Configuration of the assembly
  #   according to the selected components:
set(SPEC_DEFINITIONS    
      ${CMAKE_SYSTEM_NAME}            
      ${CMAKE_BUILD_TYPE}
      ${SPEC_BUILD}
      SPEC_VERSION="${Proj_VERSION}"
      SPEC_SERVICE="${Proj_SERVICE}"
  )

include(cmake/common.cmake)

#if (CREATE_GUI)
if (CREATE_GUI STREQUAL "ON")
  message(STATUS "Building GUI..")
  add_subdirectory(src/main_gui)
endif()

#if (CREATE_SERVICE)
if (CREATE_SERVICE STREQUAL "ON")
  message(STATUS "Building Service..")
  add_subdirectory(src/main_service)
endif()

if (CREATE_TESTS STREQUAL "ON")
  message(STATUS "Building Tests..")
  add_subdirectory(src/main_test)
endif()
