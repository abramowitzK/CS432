cmake_minimum_required(VERSION 3.3)
project(Assignment3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
set(SOURCE_FILES
        "Assignment3/Common/InitShader.cpp"
        "Assignment3/include/Angel.h"
        "Assignment3/include/CheckError.h"
        "Assignment3/include/mat.h"
        "Assignment3/include/vec.h"
        "Assignment3/main.cpp"
        "Assignment3/RegularPolygon.cpp"
        "Assignment3/RegularPolygon.h"
        "Assignment3/Vertex.h"
        "Assignment3/Shape.h" Assignment3/Ellipsoid.cpp Assignment3/Ellipsoid.h Assignment3/Triangle.cpp Assignment3/Triangle.h)
include_directories(Assignment3/include)

add_executable(Assignment3 ${SOURCE_FILES})
target_compile_options(Assignment3 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment3 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})