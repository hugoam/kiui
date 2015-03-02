# KIUI BUILD SYSTEM

cmake_minimum_required(VERSION 2.6)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

project(KIUI)

set(CMAKE_MODULE_PATH ${KIUI_SOURCE_DIR}/cmake/modules ${KIUI_SOURCE_DIR}/cmake/packages ${CMAKE_MODULE_PATH})

set(WARNING_LEVEL "/W4")
 
add_definitions("-DOBJECT_EXPORT")
add_definitions("-DUI_EXPORT")

if (MSVC)
	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif ()

find_package(OpenGL)
find_package(GLFW)
		
add_subdirectory(src)