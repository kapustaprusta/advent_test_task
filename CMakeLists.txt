# init
cmake_minimum_required(VERSION 3.10)
project(path_finder)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON   )
set(CMAKE_AUTOUIC ON   )
SET(GUI_TYPE      WIN32)

set(CMAKE_PREFIX_PATH          $ENV{Qt} )
set(CMAKE_AUTOUIC_SEARCH_PATHS res/forms)

# additional directories
include_directories(${CMAKE_BINARY_DIR})

# libraries and sources
find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui     REQUIRED)

set(SOURCES
    main.cpp
    
    src/main_window/main_window.h
    src/main_window/main_window.cpp

    src/settings_window/settings_window.h
    src/settings_window/settings_window.cpp

    src/settings_manager/settings_manager.h
    src/settings_manager/settings_manager.cpp

    src/cell_item/cell_item.h
    src/cell_item/cell_item.cpp
    
    src/randomizer/randomizer.h
    src/randomizer/randomizer.cpp

    src/defs/defs.h
)

# qt5
qt5_add_resources(SOURCES res/path_finder.qrc)

qt5_wrap_ui(SOURCES res/forms/main_window.ui
                    res/forms/settins_window.ui
)

# executable
add_executable(path_finder ${GUI_TYPE} ${SOURCES} res/path_finder.rc)

set_target_properties(path_finder PROPERTIES OUTPUT_NAME "Path Finder")

target_link_libraries(path_finder PUBLIC Qt5::Core
                                  PUBLIC Qt5::Widgets
                                  PUBLIC Qt5::Gui
)

# deploy
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E
        env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
        "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>"
        COMMENT "Running windeployqt..."
)
