cmake_minimum_required(VERSION 2.6)

aux_source_directory(. DIR_LIB_SRCS)

add_library(OpenCL ${DIR_LIB_SRCS})

find_package (OPENCL REQUIRED)
include_directories( ${OPENCL_INCLUDE_DIRS} )

target_link_libraries(OpenCL ${OPENCL_LIBRARIES})

