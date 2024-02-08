cmake_minimum_required(VERSION 3.26)
project(NNC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(NNC main.cpp
        App.cpp
        App.h
        header.h
        Node.cpp
        Node.h)
target_link_libraries(NNC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

