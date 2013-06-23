cmake_minimum_required (VERSION 2.8.1)
include_directories(../../twoD/base ../../twoD/objects)
link_directories(../../twoD)
project(libtwod-examples-basic)
include(../common.cmake)
add_executable(basic
	basic.cpp
	test.cpp
)
target_link_libraries(basic libtwod.so)
