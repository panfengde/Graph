cmake_minimum_required(VERSION 3.18.0)
project(Graph)
set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/include/IncludeBase")
include_directories("${CMAKE_SOURCE_DIR}/src")

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
message("${SOURCE_DIR}")

include_directories(./include/includePhone)
file(GLOB_RECURSE INCLUDE_SOURCE_FILES "include/includePhone/*.c" "include/includePhone/*.cpp")

file(GLOB_RECURSE SRC_FILES "${SOURCE_DIR}/*.cpp")

message("${SRC_FILES}")

file(GLOB_RECURSE TOOL_SRC_FILES "${CMAKE_SOURCE_DIR}/tool/*.cpp")
add_library(toolModule STATIC ${TOOL_SRC_FILES})

include_directories("${CMAKE_SOURCE_DIR}/registerMethod")

set(GLFM_HEADERS include/IncludePhone/glfm.h)
set(GLFM_SRC include/IncludePhone/glfmSource/glfm_internal.h include/IncludePhone/glfmSource/glfm_android.c)

add_library(glfm ${GLFM_SRC} ${GLFM_HEADERS})

find_library(log-lib log)
find_library(android-lib android)
find_library(EGL-lib EGL)
find_library(GLESv3-lib GLESv3)
target_link_libraries(glfm ${log-lib} ${android-lib} ${EGL-lib} ${GLESv3-lib})
add_library(androidGraphEntry SHARED
        ${INCLUDE_SOURCE_FILES}
        ${SRC_FILES}
        androidGraphEntry.cpp cppWithJava.cpp)
target_include_directories(androidGraphEntry PUBLIC "include")
target_link_libraries(androidGraphEntry PRIVATE toolModule glfm)



