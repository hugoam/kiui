file(GLOB SOURCE_FILES example.cpp)

add_executable(example ${SOURCE_FILES})

include_directories(${KIUI_SOURCE_DIR}/src)

target_link_libraries(example kiui)