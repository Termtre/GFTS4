cmake_minimum_required(VERSION 3.1.0)

project(main)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Charts)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(project_sources
    src/spline.cpp
    src/task.cpp
    ui/customview.cpp
    ui/functions.cpp
    ui/main.cpp
    ui/mainpart.cpp
    ui/mainwindow.cpp
    ui/oscillpart.cpp
    ui/testpart.cpp
)

set(project_headers
    include/spline.h
    include/task.h
    ui/customview.h
    ui/functions.h
    ui/mainwindow.h
)

set(project_forms
    ui/mainwindow.ui
)
add_executable(main
    ${project_sources}
    ${project_headers}
    ${project_forms}
)

target_link_libraries(main PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Charts
)

set_target_properties(main PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
