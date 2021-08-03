# ROOT CMAKE FILE
cmake_minimum_required(VERSION 3.15)
project(boostPreProduction VERSION 1.0.0)

set(CMAKE_CXX_STANDART 14)
set(CMAKE_CXX_STANDART_REQUIRED True)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(external/googletest)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)