file(GLOB SOURCE_FILES example_nanovg.cpp example.cpp)
file(GLOB HEADER_FILES example.h)

add_executable(kiui_example ${SOURCE_FILES})

include_directories(${KIUI_SOURCE_DIR}/src)
include_directories(${KIUI_SOURCE_DIR}/example)

target_link_libraries(kiui_example kiui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

install(TARGETS kiui_example RUNTIME DESTINATION bin)