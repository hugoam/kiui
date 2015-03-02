# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Object/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/Util/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/String/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/Image/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Form/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Frame/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Widget/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Scheme/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Controller/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/*.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/*.h")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Object/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/Util/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/String/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Object/Image/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Form/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Frame/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Widget/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Scheme/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Controller/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/nanovg/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/nanovg/*.c"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/Nano/*.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Ui/*.cpp")

add_library(kiui SHARED ${SOURCE_FILES})

target_link_libraries(kiui ${OPENGL_LIBRARIES})
target_link_libraries(kiui ${GLFW_LIBRARIES})

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

install(FILES ${HEADERS_FILES} DESTINATION "include")
 
#install(TARGETS kiui LIBRARY DESTINATION "lib")