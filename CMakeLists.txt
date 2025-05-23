cmake_minimum_required(VERSION 3.15)

project(sunpos VERSION 0.1.0
        DESCRIPTION "Updated PSA sun position algorithm (sunpos())")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create a reusable static library
add_library(sunpos STATIC
    src/sunpos.cpp
)

target_include_directories(sunpos PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optional test executable (only for dev/testing)
add_executable(TestOfUpdatedSunPos src/main.cpp)
target_link_libraries(TestOfUpdatedSunPos PRIVATE sunpos)