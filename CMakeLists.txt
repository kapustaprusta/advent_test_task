# init
cmake_minimum_required(VERSION 3.10)
project(path_finder)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

IF(WIN32)
    SET(GUI_TYPE WIN32)
ENDIF(WIN32)

IF(UNIX)
    SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF(UNIX)

# additional directories
include_directories(${CMAKE_BINARY_DIR})

# libraries and sources
find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui     REQUIRED)

set(SOURCES main.cpp)

# qt5
qt5_wrap_ui(SOURCES res/forms/main_window.ui)

# executable
add_executable(path_finder ${GUI_TYPE} ${SOURCES})

set_target_properties(path_finder PROPERTIES OUTPUT_NAME "Path Finder")

target_link_libraries(path_finder PUBLIC Qt5::Core
                                  PUBLIC Qt5::Widgets
                                  PUBLIC Qt5::Gui
)