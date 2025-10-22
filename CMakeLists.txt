cmake_minimum_required(VERSION 4.0)
project(Tile3 C)

file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.0/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

set(GRAPHICS GRAPHICS_API_OPENGL_43 CACHE STRING "Graphics API version for Raylib" FORCE)
CPMAddPackage("gh:raysan5/raylib#5.5")
set(CMAKE_C_STANDARD 23)

add_executable(Tile3 main.c)

target_link_libraries(Tile3 PUBLIC raylib)


add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources"
)