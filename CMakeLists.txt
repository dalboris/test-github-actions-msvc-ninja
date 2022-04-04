cmake_minimum_required(VERSION 3.12...3.22)
project(test)

# Freetype
message(STATUS "[FreeType]")
find_package(Freetype REQUIRED)
if(NOT FREETYPE_VERSION_STRING)
	message(STATUS "No FREETYPE_VERSION_STRING, getting it ourselves")
    # Sometimes, VERSION_STRING isn't defined, so we do it ourselves. See:
    # https://github.com/microsoft/vcpkg/issues/12848
    # https://github.com/vgc/vgc/pull/413
    set(FREETYPE_H "")
	get_target_property(FREETYPE_INCLUDE_DIRS Freetype::Freetype INTERFACE_INCLUDE_DIRECTORIES)
    foreach(h ${FREETYPE_INCLUDE_DIRS})
        if(NOT FREETYPE_H)
            # Yes, FreeType's include hierarchy is a mess, and not all
            # configurations provide the same include dirs.
            if (EXISTS "${h}/freetype/freetype.h")
                set(FREETYPE_H "${h}/freetype/freetype.h")
            elseif (EXISTS "${h}/freetype.h")
                set(FREETYPE_H "${h}/freetype.h")
            endif()
        endif()
    endforeach()
    if(FREETYPE_H)
        file(READ "${FREETYPE_H}" FREETYPE_H_STR)
        string(REGEX MATCH "define[ \t]+FREETYPE_MAJOR[ \t]+([0-9]+)" FREETYPE_MAJOR_MATCH "${FREETYPE_H_STR}")
        set(FREETYPE_VERSION_MAJOR "${CMAKE_MATCH_1}")
        string(REGEX MATCH "define[ \t]+FREETYPE_MINOR[ \t]+([0-9]+)" FREETYPE_MINOR_MATCH "${FREETYPE_H_STR}")
        set(FREETYPE_VERSION_MINOR "${CMAKE_MATCH_1}")
        string(REGEX MATCH "define[ \t]+FREETYPE_PATCH[ \t]+([0-9]+)" FREETYPE_PATCH_MATCH "${FREETYPE_H_STR}")
        set(FREETYPE_VERSION_PATCH "${CMAKE_MATCH_1}")
        set(FREETYPE_VERSION_STRING "${FREETYPE_VERSION_MAJOR}.${FREETYPE_VERSION_MINOR}.${FREETYPE_VERSION_PATCH}")
    endif()
endif()
message(STATUS "Version: ${FREETYPE_VERSION_STRING}")


add_executable(test main.cpp)
target_link_libraries(test Freetype::Freetype)

