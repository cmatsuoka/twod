cmake_minimum_required (VERSION 2.8.1)
include_directories(../../twoD/base ../../twoD/objects)
link_directories(../../twoD)
project(libtwod-examples-platform)
include(../common.cmake)
add_executable(platform
	character.cpp
	info.cpp
	platform.cpp
	wall.cpp
)
target_link_libraries(platform libtwod.so)
