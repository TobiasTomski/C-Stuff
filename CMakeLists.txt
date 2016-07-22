cmake_minimum_required(VERSION 3.2.2) # CMake version check
project(C-Stuff)               # Create project "simple_example"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # Enable c++11 standard
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lnetcdf")
set(SOURCE_FILES read_netcdf4.c)            # Add main.cpp file of project root directory as source file
add_executable(C-Stuff ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable