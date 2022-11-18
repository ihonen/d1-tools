include(ExternalProject)

# ------------------------------------------------------------------------------
# bzip2
# ------------------------------------------------------------------------------

ExternalProject_Add(extern-proj-bzip2
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bzip2
    BINARY_DIR ${CMAKE_BINARY_DIR}/extern/bzip2
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND   ""
    INSTALL_COMMAND  ""
    CMAKE_ARGS   "-DENABLE_LIB_ONLY=YES -DENABLE_STATIC_LIB=YES -DENABLE_SHARED_LIB=NO"
)

#SET(FXCM_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rd_party/src/ForexConnectDownload/include)
#SET(FXCM_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rd_party/src/ForexConnectDownload/lib)

#add_library(extern-lib-bz2 STATIC IMPORTED)
#set_target_properties(extern-lib-bz2
#    PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/extern/bzip2/Release/bzip2.lib
#)

#set(ENABLE_LIB_ONLY    ON CACHE INTERNAL "" FORCE)
#set(ENABLE_STATIC_LIB  ON CACHE INTERNAL "" FORCE)
#set(ENABLE_SHARED_LIB OFF CACHE INTERNAL "" FORCE)
#set(ENABLE_APP        OFF CACHE INTERNAL "" FORCE)
#
#add_subdirectory(bzip2)
#
## Make sure that these don't conflict with something else:
#unset(ENABLE_LIB_ONLY)
#unset(ENABLE_STATIC_LIB)
#unset(ENABLE_SHARED_LIB)
#unset(ENABLE_APP)
#

# ------------------------------------------------------------------------------
# mio
# ------------------------------------------------------------------------------

add_subdirectory(mio)
