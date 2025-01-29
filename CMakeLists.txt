# set minimum cmake version
cmake_minimum_required(VERSION 3.10)

# set c standard and enforce
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set build type
set(CMAKE_BUILD_TYPE Debug)

# create project
project(gd-emulator VERSION 1.0 LANGUAGES C)

# create an exectuable
add_executable(gb-emulator main.c)

