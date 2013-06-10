cmake_minimum_required (VERSION 2.8.1)
project(libtwod-examples-basic)
add_executable(basic
	basic.cpp
	test.cpp
)
include_directories(../../twoD/base ../../twoD/objects)
target_link_libraries(basic libtwod.so)
