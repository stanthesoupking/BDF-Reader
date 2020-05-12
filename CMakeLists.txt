cmake_minimum_required(VERSION 3.10)

project(BDF_Reader VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
file(GLOB_RECURSE BDF_Reader_Source "src/**.cpp")

add_executable(BDF_Reader ${BDF_Reader_Source})