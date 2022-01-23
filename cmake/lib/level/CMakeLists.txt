add_library(d1-level
    ${CMAKE_SOURCE_DIR}/src/lib/level/level.cc
    ${CMAKE_SOURCE_DIR}/src/lib/level/map.cc
    ${CMAKE_SOURCE_DIR}/src/lib/level/minimap.cc
)
target_include_directories(d1-level
    PRIVATE ${D1_INCLUDE_DIRECTORIES}
)
target_compile_options(d1-level
    PRIVATE ${D1_COMPILE_OPTIONS}
)
target_link_libraries(d1-level
    PRIVATE bz2_static
    PRIVATE mio
)
