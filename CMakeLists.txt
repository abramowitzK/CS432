cmake_minimum_required(VERSION 3.3)
project(Assignment8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
file(GLOB SOURCE_FILES
        "Assignment8/*.h"
        "Assignment8/*.cpp"
        "Assignment8/Common/*.cpp"
        )
include_directories(Assignment8/include)

add_executable(Assignment8 ${SOURCE_FILES})
target_compile_options(Assignment8 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment8 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})