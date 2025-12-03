cmake_minimum_required(VERSION 3.16)

project(TestRhiWindow LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../LibQrhiExample")
set(PROJECT_SOURCES main.cpp)

qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::GuiPrivate Qt${QT_VERSION_MAJOR}::Core
                                              LibQrhiExample)

qt_finalize_executable(${PROJECT_NAME})
