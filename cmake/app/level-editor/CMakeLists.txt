find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# -----------------------------------------------------------------------------

add_executable(d1-level-editor
    ${CMAKE_SOURCE_DIR}/src/app/level-editor/main.cc
    ${CMAKE_SOURCE_DIR}/src/app/level-editor/mainwindow.cc
    ${CMAKE_SOURCE_DIR}/src/app/level-editor/mapview.cc
    ${CMAKE_SOURCE_DIR}/src/app/level-editor/propertyview.cc
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
    PRIVATE d1-common
    PRIVATE d1-file
    PRIVATE d1-image
    PRIVATE d1-level
)
# TODO: This only works with Visual Studio (the output path is different if
# building manually on the command line).
add_custom_command(
    TARGET d1-level-editor POST_BUILD
    COMMAND ${Qt5_DIR}/bin/windeployqt.exe ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/d1-level-editor.exe
)
