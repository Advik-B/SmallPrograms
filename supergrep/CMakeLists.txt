cmake_minimum_required(VERSION 3.26)
project(SuperGrep)

set(CMAKE_CXX_STANDARD 17)

# Rename the executable to sg.exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(SuperGrep main.cpp)

set_target_properties(SuperGrep PROPERTIES OUTPUT_NAME "sg")
