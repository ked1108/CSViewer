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
qt5_add_resources(RESOURCES resources.qrc)
add_executable(CSViewer main.cpp
        mainwindow.cpp)
target_link_libraries(CSViewer
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        parser
)
target_sources(CSViewer PRIVATE ${RESOURCES})
