cmake_minimum_required(VERSION 3.3)
project(Assignment5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
SET(GCC_COVERAGE_COMPILE_FLAGS -Wall -pedantic)
SET(GCC_COVERAGE_LINK_FLAGS "-lGLEW -lGL -lglut")
file(GLOB SOURCE_FILES
        "Assignment5/*.h"
        "Assignment5/*.cpp"
        "Assignment5/Common/*.cpp"
        )
include_directories(Assignment5/include)

add_executable(Assignment5 ${SOURCE_FILES} Assignment5/SMFMeshLoader.cpp Assignment5/SMFMeshLoader.h Assignment5/Mesh.cpp Assignment5/Mesh.h Assignment5/StringUtil.h.cpp)
target_compile_options(Assignment5 PRIVATE ${GCC_COVERAGE_COMPILE_FLAGS})
target_link_libraries(Assignment5 PRIVATE ${GCC_COVERAGE_LINK_FLAGS})