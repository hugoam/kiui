# KIUI BUILD SYSTEM

cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

project(KIUI)

set(CMAKE_MODULE_PATH ${KIUI_SOURCE_DIR}/cmake/modules ${KIUI_SOURCE_DIR}/cmake/packages ${CMAKE_MODULE_PATH})

if (MSVC)
    add_compile_options(/W4)
#else ()
#    add_compile_options("-Wall -Wno-long-long -pedantic")
endif ()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=gnu++11)
    add_definitions("-DSTD_NO_MAKE_UNIQUE")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
    add_definitions("-DSTD_NO_MAKE_UNIQUE")
endif ()

find_package(OpenGL)
find_package(GLFW)

if (WIN32)
    add_definitions(-DKIUI_EXAMPLE_RESSOURCE_PATH="${CMAKE_INSTALL_PREFIX}/data/")
else ()
    add_definitions(-DKIUI_EXAMPLE_RESSOURCE_PATH="${CMAKE_INSTALL_PREFIX}/kiui/data/")
endif ()

add_subdirectory(src)

set(KIUI_BUILD_EXAMPLE yes CACHE BOOL "Build example kiui app")
if (KIUI_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if (WIN32)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION data)
else ()
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION kiui/data)
endif ()