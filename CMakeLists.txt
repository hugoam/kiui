# KIUI BUILD SYSTEM

cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

project(KIUI)

set(CMAKE_MODULE_PATH ${KIUI_SOURCE_DIR}/cmake/modules ${KIUI_SOURCE_DIR}/cmake/packages ${CMAKE_MODULE_PATH})

if (MSVC)
    set(WARNING_LEVEL "/W4")
    add_compile_options(${WARNING_LEVEL})
#else ()
#    add_compile_options("-Wall -Wno-long-long -pedantic")
endif ()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    add_compile_options("-std=gnu++0x")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    add_compile_options("-std=c++0x")
endif ()


find_package(OpenGL)
find_package(GLFW)
		
add_subdirectory(src)
add_subdirectory(example)