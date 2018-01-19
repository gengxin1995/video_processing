//#include <oclUtils.h>
#include <CL/cl.h>
#include <iostream>
//#include "cv.h"
#include "cxmisc.h"
//#include "highgui.h"
#include <opencv2/opencv.hpp>
//#include <opencv2/xfeatures2d.hpp>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "opencv2/imgcodecs.hpp"
#include <math.h>//平方根计算

#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "GPUTransferManager.h"
#include "GPUImageProcessor.h"
#include "SIFT.h"
#include "stdafx.h"
#include "sift2.h"

#include "utils.h"
#include "kdtree.h"
#include "unistd.h"//for sleep

#include <fstream>
#include <iostream>
#include <sstream>

using namespace cv; //包含cv命名空间
using namespace std;

Mat MoveDetect(Mat temp, Mat frame);

/* the maximum number of keypoint NN candidates to check during BBF search */
#define KDTREE_BBF_MAX_NN_CHKS 200

/* threshold on squared ratio of distances between NN and 2nd NN */
#define NN_SQ_DIST_RATIO_THR 0.49

int main(int argc, const char** argv) {

	VideoCapture cap;

    cap.open("/home/xin/Desktop/mydata/test0.avi");
	if (!cap.isOpened())
	{
		printf("can not open camera or video file\n");
		return -1;
	}

    int flag=1;//0:CPU;1:GPU

    //Mat img = imread("/home/xin/Desktop/CPU_SIFT/test.png", CV_LOAD_IMAGE_COLOR);//模版图像

	/**
     * Declaration for SIFT
     */

	int display = 1;
	int intvls = SIFT_INTVLS;
	double sigma = SIFT_SIGMA;
	float contr_thr = 0.04;
	int curv_thr = SIFT_CURV_THR;
	int img_dbl = SIFT_IMG_DBL;
	int descr_width = SIFT_DESCR_WIDTH;
	int descr_hist_bins = SIFT_DESCR_HIST_BINS;
	feature* features;
	int n = 0;


	SIFTGPU* siftGPU = new SIFTGPU();

	int tmp = cvRound( 0.5 );

	IplImage* img1, * img2, * stacked;
	feature* feat1, * feat2, * feat;
	feature** nbrs;
	struct kd_node* kd_root;
	CvPoint pt1, pt2;
	double d0, d1;
	int n1, n2, k, i, m = 0;

	int id = 0;

	clock_t start, finish;
	double duration = 0;
    start = clock();
	//START

        int frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);//获取帧数
        double FPS = cap.get(CV_CAP_PROP_FPS);//获取FPS
        Mat frame;//存储帧
        Mat temp;//存储前一帧图像
        Mat result;//存储结果图像
        for (int i = 0; i < frameCount; i++)
        {

            cap >> frame;//读帧进frame
            imshow("frame", frame);
            if (frame.empty()) { //对帧进行异常检测
                cout << "frame is empty!" << endl;
                break;
            }
            IplImage imgIpl1 = (IplImage)(frame);
            img1 = &imgIpl1;

            //sift-extract features
            n1 = siftGPU->_sift_features( img1, &feat1, intvls, sigma, contr_thr, curv_thr, img_dbl, descr_width, descr_hist_bins, flag);
        }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "SIFT Time cost: " << duration << endl;
	return 0;
}

