cmake_minimum_required(VERSION 3.3)
project(Assignment7)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
file(GLOB SOURCE_FILES
        "Assignment7/*.h"
        "Assignment7/*.cpp"
        "Assignment7/Common/*.cpp"
        )
include_directories(Assignment7/include)

add_executable(Assignment7 ${SOURCE_FILES})
target_compile_options(Assignment7 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment7 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})