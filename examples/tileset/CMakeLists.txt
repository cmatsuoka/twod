cmake_minimum_required (VERSION 2.8.1)
project(libtwod-examples-tileset)
include(../common.cmake)
add_executable(tileset
	tileset.cpp
)
include_directories(../../twoD/base ../../twoD/objects)
target_link_libraries(tileset libtwod.so)
