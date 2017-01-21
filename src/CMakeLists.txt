project(toyui)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB HEADER_FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Controller/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Device/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Edit/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Frame/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Input/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Gl/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Scheme/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Style/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Widget/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/nanovg/src/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/include/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/include/win32/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/*.h")

file(GLOB SOURCE_FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Controller/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Device/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Edit/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Frame/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Input/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Gl/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/RectPacking/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Scheme/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Style/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Widget/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/nanovg/src/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/nanovg/src/*.c"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/src/*.c"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/*.cpp")

option(TOYUI_PRINT_SOURCES "Print source files list" OFF)
if (TOYUI_PRINT_SOURCES)             
    message(${SOURCE_FILES})
endif ()

add_definitions("-DUI_EXPORT")

add_definitions("-DNANOVG_GLEW")
add_definitions("-DYAML_DECLARE_STATIC")

option(TOYUI_GLEW_IN_SOURCE "Build glew in source" ON)
if (TOYUI_GLEW_IN_SOURCE)
    add_definitions("-DGLEW_STATIC")
else ()
    if (GLEW_FOUND)
        include_directories($(GLEW_INCLUDE_DIRS))
    endif()
endif ()


if (MSVC)
	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
	include(CheckIncludeFiles)
	CHECK_INCLUDE_FILES(dirent.h HAVE_DIRENT_API) #Check for dirent.h header in MSVC include directories
	if (NOT HAVE_DIRENT_API)
		message(FATAL_ERROR "MSVC has no support for Dirent API, please include the header manually. See: http://www.softagalleria.net/dirent.php")
	endif()
endif ()

option(${PROJECT_NAME_UPPER}_STATIC "Build static lib instead dynamic one" OFF)
set(LIB_TYPE SHARED)
if (${PROJECT_NAME_UPPER}_STATIC)
	set(LIB_TYPE STATIC)
    set_target_properties(toyui PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif ()

add_library(toyui ${LIB_TYPE} ${SOURCE_FILES} ${HEADER_FILES})

if (NOT NANOVG_INCLUDE_DIR)
    set(NANOVG_INCLUDE_DIR ${TOYUI_INCLUDE_DIR}/Ui/Nano/nanovg/)
endif ()

include_directories(${TOYOBJ_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/nanovg/src/)
include_directories(${NANOVG_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

target_link_libraries(toyui toyobj)
target_link_libraries(toyui ${GLFW_LIBRARIES})
target_link_libraries(toyui ${OPENGL_LIBRARIES})


set(${PROJECT_NAME_UPPER}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
    
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/kiui)

if (WIN32)
	install(TARGETS toyui INCLUDES DESTINATION include ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
else ()
	install(TARGETS toyui LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif ()
