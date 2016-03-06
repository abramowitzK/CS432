cmake_minimum_required(VERSION 3.3)
project(Assignment9P1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
file(GLOB SOURCE_FILES
        "Assignment9P1/*.h"
        "Assignment9P1/*.cpp"
        "Assignment9P1/Common/*.cpp"
        )
include_directories(Assignment9P1/include)

add_executable(Assignment9P1 ${SOURCE_FILES})
target_compile_options(Assignment9P1 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment9P1 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})