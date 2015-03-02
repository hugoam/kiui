# Custom cmake module for CEGUI to find glfw

include(FindPackageHandleStandardArgs)

set(GLFW_INCLUDE_PATHS
		${PROJECT_SOURCE_DIR}/../../external/glfw/include
		${PROJECT_SOURCE_DIR}/../external/glfw/include
		/usr/local/include
		/usr/X11/include
		/usr/include
		/opt/local/include
)

set(GLFW_LIB_PATHS
		${PROJECT_SOURCE_DIR}/../../external/glfw/include
		${PROJECT_SOURCE_DIR}/../external/glfw/include
		/usr/local/include
		/usr/X11/include
		/usr/include
		/opt/local/include
)

if(WIN32)
	set(GLFW_INCLUDE_PATHS $ENV{PROGRAMFILES}/GLFW/include ${GLFW_INCLUDE_PATHS})
	set(GLFW_LIB_PATHS $ENV{PROGRAMFILES}/GLFW/lib ${GLFW_LIB_PATHS})
endif()


find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h PATHS ${GLFW_INCLUDE_PATHS} NO_DEFAULT_PATH)

find_library(GLFW_LIBRARIES NAMES glfw glfw3 PATHS ${GLFW_LIB_PATHS} PATH_SUFFIXES a lib64 lib NO_DEFAULT_PATH)

find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARIES GLFW_INCLUDE_DIR)