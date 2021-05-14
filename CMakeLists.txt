cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

# set the project name
project(Fragment)

# add the executable
add_executable(Fragment main.cpp glad/glad.c)


# GLFW3
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(./glfw)
target_link_libraries(Fragment glfw)

if (APPLE)
    target_link_libraries(Fragment "-framework OpenGL")
endif()
