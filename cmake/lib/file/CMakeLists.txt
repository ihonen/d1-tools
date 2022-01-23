add_library(d1-file
    ${CMAKE_SOURCE_DIR}/src/lib/file/dvd/bgnd.cc    
    ${CMAKE_SOURCE_DIR}/src/lib/file/dvd/file.cc
    ${CMAKE_SOURCE_DIR}/src/lib/file/dvd/sector.cc
    ${CMAKE_SOURCE_DIR}/src/lib/file/dvm/file.cc
)
target_include_directories(d1-file
    PRIVATE ${D1_INCLUDE_DIRECTORIES}
)
target_compile_options(d1-file
    PRIVATE ${D1_COMPILE_OPTIONS}
)
