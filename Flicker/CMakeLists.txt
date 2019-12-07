add_executable(Flicker main.cpp glad.c)

target_include_directories(Flicker PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Flicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_library(LIB_ASSIMP NAMES assimp PATHS ${LIB_DIR})
find_library(LIB_GLFW NAMES glfw3 glfw3dll PATHS ${LIB_DIR})

target_link_libraries(Flicker PUBLIC  ${LIB_ASSIMP})
target_link_libraries(Flicker PUBLIC  ${LIB_GLFW})

file(COPY ${LIB_DIR}/assimp.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${LIB_DIR}/glfw3.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(ASSETS_PATH  ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

add_definitions(-DASSETS_PATH="${ASSETS_PATH}")

# target_compile_definitions(Flicker PUBLIC ASSETS_PATH=${ASSETS_PATH})

add_custom_command(TARGET Flicker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${ASSETS_OUTPUT_PATH})
add_custom_command(TARGET Flicker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_PATH} ${ASSETS_OUTPUT_PATH})

add_subdirectory(Application)
add_subdirectory(Renderer)
add_subdirectory(Shader)
add_subdirectory(Assets)
