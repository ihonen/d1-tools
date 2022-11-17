add_executable(data-compiler
    main.cc
)

install(
    TARGETS data-compiler
    DESTINATION bin/
)
