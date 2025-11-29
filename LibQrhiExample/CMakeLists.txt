# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(LibQrhiExample LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_DIR "${CMAKE_SOURCE_DIR}/dist")

set(BUILD_SHARED_LIBS OFF)

find_package(Qt6 REQUIRED COMPONENTS Core GuiPrivate)

qt_standard_project_setup()

add_library(LibQrhiExample rhiwindow.cpp rhiwindow.h)

set_target_properties(LibQrhiExample PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(LibQrhiExample PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::GuiPrivate
)

set_source_files_properties("shaders/prebuilt/color.vert.qsb"
    PROPERTIES QT_RESOURCE_ALIAS "color.vert.qsb"
)
set_source_files_properties("shaders/prebuilt/color.frag.qsb"
    PROPERTIES QT_RESOURCE_ALIAS "color.frag.qsb"
)
set_source_files_properties("shaders/prebuilt/quad.vert.qsb"
    PROPERTIES QT_RESOURCE_ALIAS "quad.vert.qsb"
)
set_source_files_properties("shaders/prebuilt/quad.frag.qsb"
    PROPERTIES QT_RESOURCE_ALIAS "quad.frag.qsb"
)
qt_add_resources(LibQrhiExample "rhiwindow"
    PREFIX
        "/"
    FILES
        "shaders/prebuilt/color.vert.qsb"
        "shaders/prebuilt/color.frag.qsb"
        "shaders/prebuilt/quad.vert.qsb"
        "shaders/prebuilt/quad.frag.qsb"
)

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION "${CMAKE_INSTALL_DIR}/bin"
  LIBRARY DESTINATION "${CMAKE_INSTALL_DIR}/lib"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_DIR}/lib")

install(FILES rhiwindow.h DESTINATION "${CMAKE_INSTALL_DIR}/include")
