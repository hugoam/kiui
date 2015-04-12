file(GLOB SOURCE_FILES example.cpp)

add_executable(example ${SOURCE_FILES})

include_directories(${KIUI_SOURCE_DIR}/src)

target_link_libraries(example kiui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

install(TARGETS example RUNTIME DESTINATION "bin")