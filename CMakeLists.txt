cmake_minimum_required(VERSION 3.6.0)
project(NNC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED
)

add_library(libNNC SHARED IMPORTED)
set_target_properties(libNNC PROPERTIES IMPORTED_LOCATION
  ../libNNC/libNNC.so.1.0.0
  # ./src/back/build_lib/libNNC.so.1.0.0
)
target_include_directories(libNNC INTERFACE ./src/back/source/)

add_executable(NNC
    src/main.cpp
    src/front/App.cpp
    src/front/App.h
    src/front/Node.cpp
    src/front/Node.h
    src/front/graphwidget.cpp
    src/front/graphwidget.h
    src/front/Edge.cpp

)
target_link_libraries(NNC PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    libNNC
)
