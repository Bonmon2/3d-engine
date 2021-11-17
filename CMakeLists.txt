cmake_minimum_required(VERSION 3.20)

project(3d-Engine)

add_executable(${PROJECT_NAME} main.c)


#Include GLFW header files and Link GLFW library
include_directories(${CMAKE_SOURCE_DIR}/GLFW/include)

FILE(GLOB lib "GLFW/lib/libglfw3.a")

#Checks for library file
if(lib)
find_library(GLFW glfw3 GLFW/lib)

target_link_libraries(${PROJECT_NAME} ${GLFW})

else()
message(FATAL_ERROR "Unable to find glfw check READ ME.txt in GLFW/lib")
endif()


#Link OpenGL
find_package(OpenGL)

target_link_libraries(${PROJECT_NAME} OpenGL::GL)