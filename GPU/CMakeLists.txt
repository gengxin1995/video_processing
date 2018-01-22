include_directories(/home/genxin/opencv-3.2.0/3rdparty/include/opencl/1.2/)
include_directories(OpenCL)
include_directories(/usr/local/include/opencv)
aux_source_directory(. DIR_LIB_SRCS)

add_library(GPU_MODULE ${DIR_LIB_SRCS})


