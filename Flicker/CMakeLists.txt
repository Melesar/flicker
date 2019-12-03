add_executable(Flicker main.cpp glad.c)

target_include_directories(Flicker PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Flicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_library(LIB_ASSIMP NAMES assimp PATHS ${LIB_DIR})
find_library(LIB_GLFW NAMES glfw3 glfw3dll PATHS ${LIB_DIR})

target_link_libraries(Flicker PUBLIC  ${LIB_ASSIMP})
target_link_libraries(Flicker PUBLIC  ${LIB_GLFW})

file(COPY ${LIB_DIR}/assimp.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${LIB_DIR}/glfw3.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(RESOURCES_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

add_custom_command(TARGET Flicker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${RESOURCES_OUTPUT_PATH})
add_custom_command(TARGET Flicker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources ${RESOURCES_OUTPUT_PATH})

add_subdirectory(Application)
add_subdirectory(Renderer)
