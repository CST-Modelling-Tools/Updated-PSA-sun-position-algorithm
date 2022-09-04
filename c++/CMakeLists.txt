cmake_minimum_required(VERSION 3.0.0)
project(
    TestOfUpdatedSunPos
    VERSION 0.1.0
    DESCRIPTION "Program to test the functioning of the Updated PSA sun position algorithm; sunpos()")

add_executable(TestOfUpdatedSunPos src/main.cpp src/sunpos.cpp)

set_property(TARGET TestOfUpdatedSunPos PROPERTY CXX_STANDARD 20)

