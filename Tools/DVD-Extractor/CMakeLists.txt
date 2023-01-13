# Installed by vcpkg.
find_package(BZip2 REQUIRED)

# ------------------------------------------------------------------------------

add_executable(dvd-extractor
    main.c
)

target_compile_options(dvd-extractor
    PRIVATE /W3 /WX
)

target_compile_definitions(dvd-extractor
    PRIVATE _CRT_SECURE_NO_WARNINGS
)

target_link_libraries(dvd-extractor
    PRIVATE BZip2::BZip2
)
