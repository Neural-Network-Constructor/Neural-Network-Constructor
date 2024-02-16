cmake_minimum_required(VERSION 3.20)

project(NNC_lib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# add_executable(NNC_lib
#   ./source/main.cpp
#   ./source/Model/Layer.h
#   ./source/Model/Layer.cpp
#   ./source/Model/FullyConnectedLayer.h
#   ./source/Model/FullyConnectedLayer.cpp
#   ./source/Model/InputLayer.h
#   ./source/Model/InputLayer.cpp
#   ./source/Model/Activations.h
#   ./source/Model/Activations.cpp
#   ./source/Model/Model.h
#   ./source/Model/Model.cpp
# )

add_library(NNC_lib SHARED
  # ./source/main.cpp
  ./source/Model/Layer.h
  ./source/Model/Layer.cpp
  ./source/Model/FullyConnectedLayer.h
  ./source/Model/FullyConnectedLayer.cpp
  ./source/Model/InputLayer.h
  ./source/Model/InputLayer.cpp
  ./source/Model/Activations.h
  ./source/Model/Activations.cpp
  ./source/Model/Model.h
  ./source/Model/Model.cpp
  ./source/Model/State.cpp
  ./source/Model/State.h
)

set_target_properties(NNC_lib PROPERTIES VERSION 1.0.0)

target_include_directories(NNC_lib PRIVATE include)
install(TARGETS NNC_lib
  LIBRARY DESTINATION ./library
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
