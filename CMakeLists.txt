cmake_minimum_required(VERSION 3.5)

project(grid2gkf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(grid2gkf
    main.cpp grid2gkf.h grid2gkf.cpp record.h record.cpp)


enable_testing()
add_subdirectory(tests)
