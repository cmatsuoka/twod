cmake_minimum_required (VERSION 2.8.1)
project(libtwod-examples-platform)
include(../common.cmake)
add_executable(platform
	character.cpp
	info.cpp
	platform.cpp
	wall.cpp
)
include_directories(../../twoD/base ../../twoD/objects)
target_link_libraries(platform libtwod.so)
