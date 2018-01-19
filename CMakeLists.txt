cmake_minimum_required(VERSION 2.6)

project(video_processing)

# Find OpenCV library files
#find_package( OpenCV REQUIRED )
set(OpenCV_DIR "/home/xin/opencv-2.4.13/release")
#include_directories( ${OPENCL_INCLUDE_DIRS} )

add_subdirectory(GPU)
include_directories(/usr/local/include/opencv)
include_directories(/home/genxin/opencv-3.2.0/3rdparty/include/opencl/1.2)
aux_source_directory(. DIR_SRCS)

add_executable(video_processing ${DIR_SRCS} main.cpp)
set(OPENCL_DIR "/usr/local/cuda-8.0/lib64/libOpenCL.so")
target_link_libraries(video_processing GPU_MODULE ${OpenCV_LIBRARIES} ${OPENCL_DIR}
        -lOpenCL
        -lopencv_core
        -lopencv_highgui
        -lopencv_imgproc
        -lopencv_features2d)
