set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD   99)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ------------------------------------------------------------------------------

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set (D1_COMPILE_OPTIONS /W4)
endif ()

set(D1_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/bzip2
    ${CMAKE_SOURCE_DIR}/lib/mio/single_include
    ${CMAKE_SOURCE_DIR}/src
)

# ------------------------------------------------------------------------------

include(qtpath.cmake)

# ------------------------------------------------------------------------------

add_subdirectory(app)
add_subdirectory(lib)

# ------------------------------------------------------------------------------
