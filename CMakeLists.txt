cmake_minimum_required(VERSION 3.20.1)

project(SHA-256)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all subdirectories
add_subdirectory(lib)
add_subdirectory(src)
