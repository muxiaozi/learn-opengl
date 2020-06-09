cmake_minimum_required(VERSION 3.0)

project(LearnOpenGL)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

link_directories(${CMAKE_SOURCE_DIR}/lib)

# Find required package
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# Collect libs
set(LIBS glfw3 opengl32)

add_library(STB_IMAGE "src/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD "src/glad.c")
set(LIBS ${LIBS} GLAD)

# Create symlink
macro(makeLink src dest target)
  add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}  DEPENDS  ${dest} COMMENT "mklink ${src} -> ${dest}")
endmacro()

set(CHAPTERS
    playground
    hello-triangle
    hello-shader
    hello-texture
    hello-transform
)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/configuration
)

foreach(CHAPTER ${CHAPTERS})
    file(GLOB SOURCE
        "src/${CHAPTER}/*.h"
        "src/${CHAPTER}/*.cpp"
        "src/${CHAPTER}/*.vert"
        "src/${CHAPTER}/*.frag"
    )
    add_executable(${CHAPTER} ${SOURCE})
    target_link_libraries(${CHAPTER} ${LIBS})
    if(WIN32)
        set_target_properties(${CHAPTER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CHAPTER}")
        set_target_properties(${CHAPTER} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CHAPTER}/Debug")
    endif(WIN32)
    file(GLOB SHADERS
        "src/${CHAPTER}/*.vert"
        "src/${CHAPTER}/*.frag"
        "src/${CHAPTER}/*.geom"
    )
    foreach(SHADER ${SHADERS})
        if(WIN32)
            add_custom_command(TARGET ${CHAPTER} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:${CHAPTER}>)
        endif(WIN32)
    endforeach(SHADER)

endforeach(CHAPTER)