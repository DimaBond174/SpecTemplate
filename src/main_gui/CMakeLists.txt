# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required(VERSION 3.0)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include Qt basic functions
include(QtCommon)

# Basic information about project

# project(example VERSION 1.0)
ocv_update(CUR_EXEC_NAME "retail_mon_gui" CACHE PATH "GUI exec name")
message("CUR_EXEC_NAME: ${CUR_EXEC_NAME}")

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

# Set additional project information
set(COMPANY "Bond")
set(COPYRIGHT "Copyright (c) 2020 Bondarenko D.A. All rights reserved.")
set(IDENTIFIER "com.bond.retail_mon")

set(SOURCE_FILES
    src/main_gui.cpp
    src/gui/mainwindow.cc
    src/gui/widgets/customview.cpp
    src/presenter.cpp
    src/gui/guitools/coreicons.cpp
    ${SPEC_SRC_COMMON}/tools/spec_os.cpp
)

add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES gui_res.qrc)

#Need to provide path to Qt Widgets dir:
#if ("${Qt5Widgets_DIR}" STREQUAL "")
#  set(Qt5Widgets_DIR "/home/dbond/Qt5.13.0/5.13.0/gcc_64/lib/cmake/Qt5Widgets")
#endif()

ocv_update(Qt5Widgets_DIR "/home/dbond/Qt5.13.0/5.13.0/gcc_64/lib/cmake/Qt5Widgets" CACHE PATH "Qt5Widgets_DIR")
message("Qt5Widgets_DIR: ${Qt5Widgets_DIR}")

find_package(Qt5Widgets REQUIRED)

# source_group("UI Files" FILES ${UI_FILES})

find_package(OpenCV REQUIRED PATHS ${OPENCV_BUILD_PATH})
include_directories(${OpenCV_INCLUDE_DIRS})

set(CUR_INCLUDE
  ${OpenCV_INCLUDE_DIRS}
  ${SPEC_INCLUDE}
  )

set(CUR_LINK_LIBS
  ${OpenCV_LIBS}
  pthread  
  )

set(CUR_DEFINITIONS
    ${SPEC_DEFINITIONS}
  )

add_executable(${CUR_EXEC_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

message(STATUS "include_directories: ${CUR_INCLUDE}")
target_include_directories(${CUR_EXEC_NAME} PRIVATE ${CUR_INCLUDE})

message(STATUS "link_libraries: ${CUR_LINK_LIBS}")
target_link_libraries(${CUR_EXEC_NAME}  ${CUR_LINK_LIBS}  )

message(STATUS "CUR_DEFINITIONS: ${CUR_DEFINITIONS}")
target_compile_definitions(${CUR_EXEC_NAME} PUBLIC ${CUR_DEFINITIONS})

qt5_use_modules(${CUR_EXEC_NAME} Widgets)
