find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# -----------------------------------------------------------------------------

add_executable(d1-level-editor
    ${CMAKE_SOURCE_DIR}/src/app/level-editor/main.cc
    ${CMAKE_SOURCE_DIR}/src/app/level-editor/mainwindow.cc
)
target_include_directories(d1-level-editor
    PRIVATE ${D1_INCLUDE_DIRECTORIES}
)
target_compile_options(d1-level-editor
    PRIVATE ${D1_COMPILE_OPTIONS}
)
target_link_libraries(d1-level-editor
    PRIVATE Qt5::Widgets
)
add_custom_command(
    TARGET d1-level-editor POST_BUILD
    COMMAND $ENV{CMAKE_PREFIX_PATH}/bin/windeployqt.exe ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/d1-level-editor.exe
)

message("$ENV{CMAKE_PREFIX_PATH}\\bin\\windeployqt.exe")
