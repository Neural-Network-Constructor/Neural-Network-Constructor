cmake_minimum_required(VERSION 3.20)

project(NNC VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

add_executable(NNC
  ./source/main.cpp
  ./source/Model/Layer.h
  ./source/Model/Layer.cpp
  ./source/Model/FullyConnectedLayer.h
  ./source/Model/FullyConnectedLayer.cpp
  ./source/Model/InputLayer.h
  ./source/Model/InputLayer.cpp
  # ./source/Model/OutputLayer.h
  # ./source/Model/OutputLayer.cpp
  ./source/Model/Activations.h
  ./source/Model/Activations.cpp
  ./source/Model/Model.h
  ./source/Model/Model.cpp
)
