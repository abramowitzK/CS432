cmake_minimum_required(VERSION 3.3)
project(Assignment2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
set(SOURCE_FILES
        "Assignment2/Common/InitShader.cpp"
        "Assignment2/include/Angel.h"
        "Assignment2/include/CheckError.h"
        "Assignment2/include/mat.h"
        "Assignment2/include/vec.h"
        "Assignment2/main.cpp"
        "Assignment2/RegularPolygon.cpp"
        "Assignment2/RegularPolygon.h"
        "Assignment2/Vertex.h"
        "Assignment2/Shape.h" Assignment2/Ellipsoid.cpp Assignment2/Ellipsoid.h Assignment2/Triangle.cpp Assignment2/Triangle.h)
include_directories(Assignment2/include)

add_executable(Assignment2 ${SOURCE_FILES})
target_compile_options(Assignment2 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment2 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})