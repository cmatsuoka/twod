cmake_minimum_required (VERSION 2.8.1)
include_directories(../../twoD/base ../../twoD/objects)
link_directories(../../twoD)
project(libtwod-examples-parallax)
include(../common.cmake)
add_executable(parallax
	info.cpp
	parallax.cpp
	spaceship.cpp
)
target_link_libraries(parallax libtwod.so)
