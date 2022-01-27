if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_CXX_STANDARD 20)
else ()
    set(CMAKE_CXX_STANDARD 17)
endif ()
set(CMAKE_C_STANDARD 99)

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

include(${CMAKE_SOURCE_DIR}/cmake/qtpath.cmake)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# -----------------------------------------------------------------------------

add_executable(d1-level-editor
    app/infoview.cc
    app/main.cc
    app/mainwindow.cc
    app/levelscene.cc
    app/levelview.cc
    app/propertyview.cc
    common/bzip2
    common/log.cc
    file/dvd/bgnd.cc
    file/dvd/buil.cc
    file/dvd/file.cc
    file/dvd/sector.cc
    file/dvm/file.cc
    image/pixel.cc
    world/building.cc
    world/door.cc
    world/level.cc
    world/map.cc
    world/minimap.cc
)
target_include_directories(d1-level-editor
    PRIVATE ${D1_INCLUDE_DIRECTORIES}
)
target_compile_options(d1-level-editor
    PRIVATE ${D1_COMPILE_OPTIONS}
)
target_link_libraries(d1-level-editor
    PRIVATE Qt5::Widgets
    PRIVATE bz2_static
    PRIVATE mio
)
# TODO: This only works with Visual Studio (the output path is different if
# building manually on the command line).
add_custom_command(
    TARGET d1-level-editor POST_BUILD
    COMMAND ${Qt5_DIR}/bin/windeployqt.exe ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/d1-level-editor.exe
)
