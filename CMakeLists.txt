cmake_minimum_required(VERSION 3.0)

# ------------------------------------------------------------------------------

project(d1-tools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD   17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ------------------------------------------------------------------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------

add_subdirectory(Core)
add_subdirectory(Tools/DVD-Extractor)
