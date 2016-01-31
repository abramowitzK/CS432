cmake_minimum_required(VERSION 3.3)
project(Assignment4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
file(GLOB SOURCE_FILES
        "Assignment4/*.h"
        "Assignment4/*.cpp"
        "Assignment4/Common/*.cpp"
        )
include_directories(Assignment4/include)

add_executable(Assignment4 ${SOURCE_FILES})
target_compile_options(Assignment4 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment4 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})