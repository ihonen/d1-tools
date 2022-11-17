project(level-viewer)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set (D1_COMPILE_OPTIONS /W4)
endif ()

# ------------------------------------------------------------------------------

include(${CMAKE_SOURCE_DIR}/cmake/FindQt5.cmake NO_POLICY_SCOPE)

# -----------------------------------------------------------------------------

add_executable(level-viewer
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
    file/dvd/mat.cc
    file/dvd/sector.cc
    file/dvm/file.cc
    image/pixel.cc
    world/building.cc
    world/door.cc
    world/level.cc
    world/map.cc
    world/material.cc
    world/minimap.cc
)

target_include_directories(level-viewer
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${Qt5_INCLUDE_DIRS}
)

target_link_libraries(level-viewer
    PRIVATE ${Qt5Widgets_LIBRARIES}
    PRIVATE bz2_static
    PRIVATE mio
)

# TODO: This only works with Visual Studio (the output path is different if
# building manually on the command line).
add_custom_command(
    TARGET level-viewer POST_BUILD
    COMMAND ${Qt5_BIN_DIR}/windeployqt.exe ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/level-viewer.exe
)
