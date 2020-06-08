cmake_minimum_required(VERSION 3.0)

project(OpenGLDemo)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

include_directories(
    ${CMAKE_SOURCE_DIR}/3rdparty/glfw-3.3.2.bin.WIN64/include
    ${CMAKE_SOURCE_DIR}/3rdparty/glad-3.3-core/include
    ${CMAKE_SOURCE_DIR}
)

link_directories(
    ${CMAKE_SOURCE_DIR}/3rdparty/glfw-3.3.2.bin.WIN64/lib-vc2019
)

add_library(glad STATIC
    ${CMAKE_SOURCE_DIR}/3rdparty/glad-3.3-core/src/glad.c)

link_libraries(
    glfw3.lib
    opengl32.lib
    glad
)

add_subdirectory(playground)
add_subdirectory(hello-triangle)
add_subdirectory(hello-shader)
add_subdirectory(hello-texture)