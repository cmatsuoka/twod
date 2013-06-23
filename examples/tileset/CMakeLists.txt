cmake_minimum_required (VERSION 2.8.1)
include_directories(../../twoD/base ../../twoD/objects)
link_directories(../../twoD)
project(libtwod-examples-tileset)
include(../common.cmake)
add_executable(tileset
	tileset.cpp
)
target_link_libraries(tileset libtwod.so)
