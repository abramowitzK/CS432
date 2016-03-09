cmake_minimum_required(VERSION 3.3)
project(Assignment9P2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
file(GLOB SOURCE_FILES
        "Assignment9P2/*.h"
        "Assignment9P2/*.cpp"
        "Assignment9P2/Common/*.cpp"
        )
include_directories(Assignment9P2/include)

add_executable(Assignment9P2 ${SOURCE_FILES})
target_compile_options(Assignment9P2 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment9P2 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})