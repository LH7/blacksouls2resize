
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(SOURCES_version_lib
        targets/version_lib.c
        )
add_library(version_lib SHARED
        ${SOURCES_common}
        ${SOURCES_version_lib}
        res/resources.rc
        )
target_include_directories(version_lib PRIVATE include)

set_target_properties(version_lib PROPERTIES 
    OUTPUT_NAME "version"
)

list(APPEND ALL_TARGETS version_lib)
list(APPEND SOURCES_all ${SOURCES_version_lib})
