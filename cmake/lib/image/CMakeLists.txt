add_library(d1-image
    ${CMAKE_SOURCE_DIR}/src/lib/image/pixel.cc
)
target_include_directories(d1-image
    PRIVATE ${D1_INCLUDE_DIRECTORIES}
)
target_compile_options(d1-image
    PRIVATE ${D1_COMPILE_OPTIONS}
)
