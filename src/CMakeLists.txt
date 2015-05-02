# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
file(GLOB HEADER_FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Object/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/Util/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/String/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/Image/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Form/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Style/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Frame/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Widget/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Scheme/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Controller/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/*.h")

file(GLOB SOURCE_FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Object/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/Util/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/String/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/Image/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Form/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Style/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Style/yaml/*.c"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Frame/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Widget/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Scheme/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Controller/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/RectPacking/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/nanovg/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/nanovg/*.c"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/*.cpp")

											
add_definitions("-DOBJECT_EXPORT")
add_definitions("-DUI_EXPORT")

add_definitions("-DNANOVG_GLEW")

if (MSVC)
	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
	include(CheckIncludeFiles)
	CHECK_INCLUDE_FILES(dirent.h HAVE_DIRENT_API) #Check for dirent.h header in MSVC include directories
	if (NOT HAVE_DIRENT_API)
		message(FATAL_ERROR "MSVC has no support for Dirent API, please include the header manually. See: http://www.softagalleria.net/dirent.php")
	endif()
endif ()

option(${PROJECT_NAME}_STATIC "Build static lib instead dynamic one")
set(LIB_TYPE SHARED)
if (${PROJECT_NAME}_STATIC)
	set(LIB_TYPE STATIC)
	if (CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		#enable Position-independent code generation for static lib
		add_definitions(-fPIC)
	endif ()
endif ()

add_library(kiui ${LIB_TYPE} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(kiui ${OPENGL_LIBRARIES})
target_link_libraries(kiui ${GLFW_LIBRARIES})

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/kiui)

if (WIN32)
	install(TARGETS kiui INCLUDES DESTINATION include ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
else ()
	install(TARGETS kiui LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif ()