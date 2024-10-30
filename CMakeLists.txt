cmake_minimum_required(VERSION 3.28)
project(Graph)

set(CMAKE_CXX_STANDARD 20)

include_directories(./include)
file(GLOB_RECURSE INCLUDE_SOURCE_FILES "include/*.c" "include/*.cpp")

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(status "now is mac")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.5")
    include_directories(/opt/homebrew/Cellar/glfw/3.3.4/include)
    link_directories(/Users/panfeng/coder/myProject/LUINeedLib)
    add_executable(Graph
            MACOSX_BUNDLE
            ${INCLUDE_SOURCE_FILES}
            main.cpp)
    target_link_libraries(Graph
            glfw
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(project_lib_include "E:/code/terminateProject")
    include_directories(${project_lib_include}/dependInclude)
    link_directories(${project_lib_include}/dependLib)
    add_executable(LUI
            ${INCLUDE_SOURCE_FILES}
            main.cpp
    )
    target_link_libraries(LUI
            glfw3
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(GLFM_HEADERS include/glfm.h)
    set(GLFM_SRC src/glfm_internal.h src/glfm_android.c)
    add_library(glfm ${GLFM_SRC} ${GLFM_HEADERS})
    add_library(Entry SHARED main.cpp)
endif ()



