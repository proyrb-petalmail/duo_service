cmake_minimum_required(VERSION 3.10)

project(service VERSION 1.0)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/main
    ${CMAKE_CURRENT_SOURCE_DIR}/main/debug
    ${CMAKE_CURRENT_SOURCE_DIR}/main/error
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/cmdline
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/configor
)

file(GLOB_RECURSE
	source_file_list
	${CMAKE_CURRENT_SOURCE_DIR}/main/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/modules/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/modules/*.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

add_executable(service ${source_file_list})
