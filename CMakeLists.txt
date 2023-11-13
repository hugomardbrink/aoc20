cmake_minimum_required(VERSION 3.21)
project(aoc20 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "g++-13")

find_package(OpenMP REQUIRED)

set(executables d1 d2)

foreach(executable ${executables})
    add_executable(${executable} "${executable}/main.cxx")
    target_compile_options(${executable} PRIVATE -lstdc++ -fopenmp )
    target_link_libraries(${executable} PRIVATE OpenMP::OpenMP_CXX)
endforeach()