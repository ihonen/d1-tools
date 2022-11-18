find_package(BZip2 REQUIRED)

# ------------------------------------------------------------------------------

add_executable(dvd-extractor
    main.c
)

target_link_libraries(dvd-extractor
    PUBLIC bz2
)

install(
    TARGETS dvd-extractor
    DESTINATION bin
)
