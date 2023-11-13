cmake_minimum_required(VERSION 3.26)
project(ImGLFW)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)

add_subdirectory(glfw)
add_subdirectory(glm)

add_executable(ImGLFW main.cpp)

# Add GLFW
target_link_libraries(ImGLFW glfw)
target_link_libraries(ImGLFW glm)
target_link_libraries(ImGLFW OpenGL::GL)


# If Release, disable console window
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(ImGLFW PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif ()
