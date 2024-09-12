cmake_minimum_required(VERSION 3.28)
project(CSViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(src)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(CSV_Viewer main.cpp
        mainwindow.cpp)
target_link_libraries(CSV_Viewer
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        parser
)
