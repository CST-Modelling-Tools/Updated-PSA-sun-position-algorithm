cmake_minimum_required(VERSION 3.15)
project(
    TestOfUpdatedSunPos
    VERSION 0.1.0
    DESCRIPTION "Program to test the functioning of the Updated PSA sun position algorithm; sunpos()")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory
include_directories(include)

# Define your source files
set(SOURCES
    src/main.cpp
    src/sunpos.cpp
)

# Create the executable
add_executable(TestOfUpdatedSunPos ${SOURCES})
