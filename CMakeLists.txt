cmake_minimum_required(VERSION 3.15)

project(sunpos VERSION 0.1.0
    DESCRIPTION "Updated PSA sun position algorithm (sunpos())"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------------
# Static library target
# ------------------------------------------------------------------------------------
add_library(sunpos STATIC
    src/sunpos.cpp
)

target_include_directories(sunpos
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ------------------------------------------------------------------------------------
# Optional test executable
# ------------------------------------------------------------------------------------
add_executable(TestOfUpdatedSunPos apps/test/main.cpp)
target_link_libraries(TestOfUpdatedSunPos PRIVATE sunpos)
target_include_directories(TestOfUpdatedSunPos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------------
# CLI executable
# ------------------------------------------------------------------------------------
add_executable(sunpos_cli apps/cli/main.cpp)
target_link_libraries(sunpos_cli PRIVATE sunpos)
target_include_directories(sunpos_cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)