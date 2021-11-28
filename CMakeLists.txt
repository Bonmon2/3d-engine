cmake_minimum_required(VERSION 3.20)

project(3d-Engine)

add_executable(${PROJECT_NAME} main.c)



#Include GLFW header files and Link GLFW library
include_directories(${CMAKE_SOURCE_DIR}/ext/GLFW/include ${CMAKE_SOURCE_DIR}/ext/glad/include)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader.vert
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader.frag
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)


FILE(GLOB lib "ext/GLFW/lib/libglfw3.a")

#Checks for library file
if(lib)
find_library(GLFW glfw3 ext/GLFW/lib)

add_subdirectory(${CMAKE_SOURCE_DIR}/ext/glad)

target_link_libraries(${PROJECT_NAME} ${GLFW} glad)

else()
message(FATAL_ERROR "Unable to find glfw check READ ME.txt in ext/GLFW/lib")
endif()


#Link OpenGL
find_package(OpenGL)

target_link_libraries(${PROJECT_NAME} OpenGL::GL)