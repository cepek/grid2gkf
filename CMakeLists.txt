cmake_minimum_required(VERSION 3.5)

project(text2xml LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gama-local-text2xml
    gama-local-text2xml.cpp
    text2xml.h text2xml.cpp)


enable_testing()
add_subdirectory(tests)
