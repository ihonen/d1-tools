add_library(d1-common
    ${CMAKE_SOURCE_DIR}/src/lib/common/bzip2.cc
    ${CMAKE_SOURCE_DIR}/src/lib/common/log.cc
)
target_include_directories(d1-common
    PRIVATE ${D1_INCLUDE_DIRECTORIES}
)
target_compile_options(d1-common
    PRIVATE ${D1_COMPILE_OPTIONS}
)
