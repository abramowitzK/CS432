cmake_minimum_required(VERSION 3.3)
project(Assignment1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
set(SOURCE_FILES
        "Assignment1/Common/InitShader.cpp"
        "Assignment1/include/Angel.h"
        "Assignment1/include/CheckError.h"
        "Assignment1/include/mat.h"
        "Assignment1/include/vec.h"
        "Assignment1/red_shapes.cpp"
        "Assignment1/RegularPolygon.cpp"
        "Assignment1/RegularPolygon.h"
        "Assignment1/Vertex.h"
        "Assignment1/Shape.h" Assignment1/Ellipsoid.cpp Assignment1/Ellipsoid.h Assignment1/Triangle.cpp Assignment1/Triangle.h)
include_directories(Assignment1/include)

add_executable(Assignment1 ${SOURCE_FILES})
target_compile_options(Assignment1 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment1 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})