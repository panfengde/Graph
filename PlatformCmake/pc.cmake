cmake_minimum_required(VERSION 3.18.0)
project(Graph)
set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/include/IncludeBase")
include_directories("${CMAKE_SOURCE_DIR}/src")

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
message("${SOURCE_DIR}")

include_directories(include/IncludePC)
file(GLOB_RECURSE INCLUDE_SOURCE_FILES "include/IncludePC/*.c" "include/IncludePC/*.cpp")
file(GLOB_RECURSE SRC_FILES "${SOURCE_DIR}/*.cpp")
message("${SRC_FILES}")

file(GLOB_RECURSE TOOL_SRC_FILES "${CMAKE_SOURCE_DIR}/tool/*.cpp")
add_library(toolModule STATIC ${TOOL_SRC_FILES})

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(status "now is mac")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.5")
    include_directories(/opt/homebrew/Cellar/glfw/3.3.4/include)
    link_directories(/Users/panfeng/coder/myProject/LUINeedLib)
    add_executable(Graph
            MACOSX_BUNDLE
            ${INCLUDE_SOURCE_FILES}
            ${SRC_FILES}
            main.cpp)
    target_link_libraries(Graph
            "-framework Foundation"
            toolModule
            glfw
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(project_lib_include "E:\\code\\LAB\\")
    include_directories(${project_lib_include}/dependInclude)
    link_directories(${project_lib_include}/dependLib)
    add_executable(Graph
            ${INCLUDE_SOURCE_FILES}
            ${SRC_FILES}
            main.cpp
    )
    target_link_libraries(Graph
            PRIVATE
            toolModule
            glfw3
    )
endif ()



