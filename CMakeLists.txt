cmake_minimum_required(VERSION 3.15)

project(Blacksouls2resize C)
enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if(POLICY CMP0115)
        cmake_policy(SET CMP0115 NEW)
endif()
add_compile_definitions(__USE_MINGW_ANSI_STDIO=0)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -Wall -flto -fdata-sections -ffunction-sections -Wl,-gc-sections -s -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCES_common
        src/dll_wrapper_jmp.s  include/dll_wrapper_exp.def
        src/dll_wrapper.c      include/dll_wrapper.h
        src/wnd_proc.c         include/wnd_proc.h
        src/wnd_search.c       include/wnd_search.h
        src/wnd_styles.c       include/wnd_styles.h
        )

set(ALL_TARGETS)
file(GLOB TARGETS_CMAKE "cmake/build_*.cmake")
foreach(target_file ${TARGETS_CMAKE})
        include(${target_file})
endforeach()
add_custom_target(_buid_all_ ALL DEPENDS ${ALL_TARGETS})

list(APPEND SOURCES_all
        res/manifest.xml
        res/resources.rc.in
        )

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/res/resources.rc
        COMMAND ${CMAKE_COMMAND}
            -DPATH_FILE_VERSION_INFO="${CMAKE_CURRENT_SOURCE_DIR}/res/resources.rc"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/generate_version.cmake"
        DEPENDS ${SOURCES_common}
        )