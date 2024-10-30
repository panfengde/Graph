
cmake_minimum_required(VERSION 3.18.0)

project(Graph)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    include_directories(./include/includePC)
    file(GLOB_RECURSE INCLUDE_SOURCE_FILES "include/includePC/*.c" "include/includePC/*.cpp")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include_directories(./include/includePC)
    file(GLOB_RECURSE INCLUDE_SOURCE_FILES "include/includePC/*.c" "include/includePC/*.cpp")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    include_directories(./include/includePhone)
    file(GLOB_RECURSE INCLUDE_SOURCE_FILES "include/includePhone/*.c" "include/includePhone/*.cpp")
endif ()


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
    include_directories(${CMAKE_BINARY_DIR}/configuration)

    set(project_lib_include "E:\\code\\LAB\\")
    include_directories(${project_lib_include}/dependInclude)
    link_directories(${project_lib_include}/dependLib)
    add_executable(Graph
            ${INCLUDE_SOURCE_FILES}
            main.cpp
    )
    target_link_libraries(Graph
            glfw3
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(GLFM_HEADERS include/IncludePhone/glfm.h)
    set(GLFM_SRC include/IncludePhone/glfmSource/glfm_internal.h include/IncludePhone/glfmSource/glfm_android.c)
    add_library(glfm ${GLFM_SRC} ${GLFM_HEADERS})

    find_library(log-lib log)
    find_library(android-lib android)
    find_library(EGL-lib EGL)
    find_library(GLESv2-lib GLESv2)
    target_link_libraries(glfm ${log-lib} ${android-lib} ${EGL-lib} ${GLESv2-lib})

    add_library(androidGraphEntry SHARED  ${INCLUDE_SOURCE_FILES} androidGraphEntry.cpp cppWithJava.cpp)
    target_include_directories(androidGraphEntry PUBLIC "include")
    target_link_libraries(androidGraphEntry glfm)
endif ()



