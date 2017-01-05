# toyui BUILD SYSTEM

cmake_minimum_required(VERSION 2.8.12)
cmake_policy(SET CMP0003 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_CURRENT_SOURCE_DIR}/cmake/packages ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    add_compile_options(/W4)
#else ()
#    add_compile_options("-Wall -Wno-long-long -pedantic")
endif ()

find_package(OpenGL)
find_package(GLFW)

add_subdirectory(sub/toy-obj/src)
add_subdirectory(src)

set(TOYUI_BUILD_EXAMPLE yes CACHE BOOL "Build example kiui app")
if (TOYUI_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if (WIN32)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION data)
else ()
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION kiui/data)
endif ()
