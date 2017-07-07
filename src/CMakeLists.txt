project(toyui)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB HEADER_FILES 	
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Button/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Container/*.h"
                        "${CMAKE_CURRENT_SOURCE_DIR}/toyui/Controller/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Edit/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Frame/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Gl/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Input/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Nano/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Render/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Solver/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Style/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Widget/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Window/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/nanovg/src/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/include/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/win32/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/src/*.h")

file(GLOB SOURCE_FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Button/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Container/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Controller/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Edit/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Frame/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Gl/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Input/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Nano/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Render/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Solver/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Style/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Widget/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/Window/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/toyui/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/nanovg-layers/src/*.c"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/src/*.c"
						"${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/rectpacking/RectPacking/*.cpp")

option(TOYUI_PRINT_SOURCES "Print source files list" OFF)
if (TOYUI_PRINT_SOURCES)             
    message(${SOURCE_FILES})
endif ()

add_definitions("-DUI_EXPORT")
add_definitions("-DTOYUI_DRAW_CACHE")
    
add_definitions("-DHAVE_CONFIG_H")
add_definitions("-DYAML_DECLARE_STATIC")

if (GLEW_FOUND)
    add_definitions("-DNANOVG_GLEW")
    add_definitions("-DGLEW_STATIC")
endif()

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


include_directories(${TOYOBJ_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/yaml/win32/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/nanovg-layers/src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/rectpacking/)
include_directories(${NANOVG_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(toyui toyobj)
target_link_libraries(toyui ${OPENGL_LIBRARIES})

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(toyui ${GLEW_LIBRARY})
    target_link_libraries(toyui ${GLEW_LIBRARIES})
endif()


set(${PROJECT_NAME_UPPER}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
    
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/kiui)

if (WIN32)
	install(TARGETS toyui INCLUDES DESTINATION include ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
else ()
	install(TARGETS toyui LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif ()
