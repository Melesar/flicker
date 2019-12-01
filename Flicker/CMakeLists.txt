add_executable(Flicker main.cpp)

target_include_directories(Flicker PUBLIC ${VENDOR_DIR}/assimp-3.1.1-win-binaries/include)
find_library(LIB_ASSIMP NAMES assimp PATHS ${LIB_DIR})
target_link_libraries(Flicker PUBLIC ${LIB_ASSIMP})


file(COPY ${LIB_DIR}/assimp.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(RESOURCES_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

message(${RESOURCES_OUTPUT_PATH})


add_custom_command(TARGET Flicker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${RESOURCES_OUTPUT_PATH})
add_custom_command(TARGET Flicker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources ${RESOURCES_OUTPUT_PATH})