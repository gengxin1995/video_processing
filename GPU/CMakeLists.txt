# Find OpenCV library files
#find_package( OpenCV REQUIRED )

#find_package (OPENCL REQUIRED)
#include_directories( ${OPENCL_INCLUDE_DIRS} )
set(OpenCV_DIR "/home/xin/opencv-2.4.13/release")
#add_subdirectory(OpenCL)
include_directories(/home/genxin/opencv-3.2.0/3rdparty/include/opencl/1.2/)
include_directories(OpenCL)
include_directories(/usr/local/include/opencv)
aux_source_directory(. DIR_LIB_SRCS)
set(OPENCL_SOURCES OpenCL/AssignOrientations.cl OpenCL/BlurGaussFilter.cl OpenCL/Binarization.cl
        OpenCL/DilateFilter.cl OpenCL/DetectExtrema.cl OpenCL/ExtractKeypointDescriptors.cl OpenCL/ErodeFilter.cl
        OpenCL/GPUCode.cl OpenCL/HighpassFilter.cl OpenCL/LUTFilter.cl OpenCL/LowpassFilter.cl OpenCL/MinFilter.cl
        OpenCL/MedianFilter.cl OpenCL/MaxFilter.cl OpenCL/RGB2YUV.cl OpenCL/RGB2HSV.cl OpenCL/Subtract.cl)

add_library(GPU_MODULE ${DIR_LIB_SRCS})
set(OPENCL_DIR "/usr/local/cuda-8.0/lib64/libOpenCL.so")

#target_link_libraries(GPU OpenCL_MODULE ${OpenCV_LIBRARIES} ${OPENCL_DIR}
#        -lOpenCL
#        -lopencv_core
#        -lopencv_highgui
#        -lopencv_imgproc
#        -lopencv_features2d)

