# Example:
# set(Qt5_DIR C:/Qt/5.15.2/msvc2019_64)
# set(Qt5Core_DIR    ${Qt5_DIR}/lib/cmake/Qt5Core)
# set(Qt5Widgets_DIR ${Qt5_DIR}/lib/cmake/Qt5Widgets)

# ------------------------------------------------------------------------------

set(Qt5_DIR        TODO)
set(Qt5Core_DIR    ${Qt5_DIR}/lib/cmake/Qt5Core)
set(Qt5Widgets_DIR ${Qt5_DIR}/lib/cmake/Qt5Widgets)

if (${Qt5_DIR} STREQUAL TODO)
    message("ERROR: You must set the value of Qt5_DIR in qtpath.cmake before building")
endif ()
