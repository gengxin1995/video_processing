////#include <oclUtils.h>
//#include <CL/cl.h>
//#include <iostream>
////#include "cv.h"
//#include "cxmisc.h"
////#include "highgui.h"
//#include <opencv2/opencv.hpp> //头文件
//#include <opencv2/xfeatures2d.hpp>
//#include <opencv/highgui.h>
//#include <opencv/cv.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
////#include "opencv2/imgcodecs.hpp"
//#include <opencv2/calib3d/calib3d.hpp>
//#include <math.h>//平方根计算
//
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <stdio.h>
//#include <ctype.h>
//#include <time.h>
//#include "GPUTransferManager.h"
//#include "GPUImageProcessor.h"
//#include "SIFT.h"
//#include "stdafx.h"
//#include "sift2.h"
//
//#include "utils.h"
//#include "kdtree.h"
//#include "unistd.h"//for sleep
//
//#include <fstream>
//#include <iostream>
//#include <sstream>
//
//using namespace cv; //包含cv命名空间
//using namespace std;
//using namespace cv::xfeatures2d;
//
///* the maximum number of keypoint NN candidates to check during BBF search */
//#define KDTREE_BBF_MAX_NN_CHKS 200
//
///* threshold on squared ratio of distances between NN and 2nd NN */
//#define NN_SQ_DIST_RATIO_THR 0.49
//
//int main(int argc, const char** argv)
//{
//
//    VideoCapture cap;
//    bool update_bg_model = true;
////    ofstream outfile("/home/genxin/data/out.txt", ofstream::app);
//
//    cap.open("/home/genxin/data/test0.avi");
//
//    //namedWindow("image", WINDOW_AUTOSIZE);
//    //namedWindow("imageROI", WINDOW_AUTOSIZE);
//
//    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();//(100, 3, 0.3, 5);
//
//    Mat img, fgmask, fgimg;
//    vector< vector<Point> > contours;
//    // vector<vector<Mat>> ROIs;//ROI[1]为第一帧所有ROI
//    vector<vector<pair<Rect,Mat> > > ROIs;
//    int flag=0;
//
//
//    /**
//     * Declaration for SIFT
//     */
//
//    int display = 1;
//    int intvls = SIFT_INTVLS;
//    double sigma = SIFT_SIGMA;
//    float contr_thr = 0.04;
//    int curv_thr = SIFT_CURV_THR;
//    int img_dbl = SIFT_IMG_DBL;
//    int descr_width = SIFT_DESCR_WIDTH;
//    int descr_hist_bins = SIFT_DESCR_HIST_BINS;
//    feature* features;
//    int n = 0;
//
//
//    SIFTGPU* siftGPU = new SIFTGPU();
//
//    int tmp = cvRound( 0.5 );
//
//    IplImage* img1, * img2, * stacked;
//    feature* feat1, * feat2, * feat;
//    feature** nbrs;
//    struct kd_node* kd_root;
//    CvPoint pt1, pt2;
//    double d0, d1;
//    int n1, n2, k, i, m = 0;
//
//    int id = 0;
//
//    clock_t start, finish;
//    double duration = 0;
//
//    //namedWindow("1");
//    //START
//    if (cap.isOpened()) {
//        while (1) {
//            cap >> img;
//
//            if (img.empty()) {
//                break;
//            }
//
//            if (fgimg.empty())
//                fgimg.create(img.size(), img.type());
//
//            vector<pair<Rect,Mat> > currentROIs;//pair: loc,ROIimage
//            bg_model->apply(img, fgmask); //build model
//
//            fgimg = Scalar::all(0);
//            img.copyTo(fgimg, fgmask);
//
//            Mat bgimg;
//            bg_model->getBackgroundImage(bgimg);
//            findContours(
//                    fgmask,
//                    contours,
//                    cv::noArray(),
//                    cv::RETR_EXTERNAL,
//                    cv::CHAIN_APPROX_SIMPLE
//            );
//
//            int size = contours.size();
//            for(int i=0; i<size; i++){
//                Rect r0= boundingRect(Mat(contours[i]));
//
//                if(r0.height*r0.width>2000){
//                    Mat imageROI;
//                    imageROI = img(r0);
//
//                    IplImage imgIpl1 = (IplImage)(imageROI);
//                    img1 = &imgIpl1;
//                    IplImage imgIpl2 = (IplImage)(img);
//                    img2 = &imgIpl2;
//
//                    start = clock();
//
//                    //sift-extract features
//                    n1 = siftGPU->_sift_features( img1, &feat1, intvls, sigma, contr_thr, curv_thr, img_dbl, descr_width, descr_hist_bins, flag);
//                    n2 = siftGPU->_sift_features( img2, &feat2, intvls, sigma, contr_thr, curv_thr, img_dbl, descr_width, descr_hist_bins, flag);
//
//                    finish = clock();
//                    duration = (double)(finish - start) / CLOCKS_PER_SEC;
//                    cout << "SIFT Time cost: " << duration << endl;
//
//                    vector<KeyPoint> kpList1;
//                    vector<KeyPoint> kpList2;
//                    kpList1.resize(n1);
//                    kpList2.resize(n2);
//
//                    for (int i = 0; i < n1; i++) {
//                        Point2f pt(feat1[i].x, feat1[i].y);
//                        kpList1[i].pt = pt;
//                    }
//
//                    for (int i = 0; i < n2; i++) {
//                        Point2f pt(feat2[i].x, feat2[i].y);
//                        kpList2[i].pt = pt;
//                    }
//
//                    Ptr<Feature2D> detector = xfeatures2d::SIFT::create();
//
//                    //find sift descriptors
//                    Mat descriptors_object, descriptors_scene;
//                    detector->compute(imageROI, kpList1, descriptors_object);
//                    detector->compute(img, kpList2, descriptors_scene);
//
//                    //use BruteForce to match,and get good_matches
//                    BFMatcher matcher;
//                    vector<DMatch> matches;
//                    matcher.match(descriptors_object, descriptors_scene, matches);
//
//                    double max_dist = 0; double min_dist = 100;
//
//                    //快速计算特征点之间的最大和最小距离
//                    for (int i = 0; i < descriptors_object.rows; i++) {
//                        double dist = matches[i].distance;
//                        if (dist < min_dist) min_dist = dist;
//                        if (dist > max_dist) max_dist = dist;
//                    }
//
//                    //printf("---Max dist: %f \n", max_dist);
//                    //printf("---Min dist: %f \n", min_dist);
//
//                    vector<DMatch> good_matches;
//
//                    for (int i = 0; i < descriptors_object.rows; i++) {
//                        if (matches[i].distance <= 3 * min_dist)
//                            good_matches.push_back(matches[i]);
//                    }
//
//                    int num = good_matches.size();
//                    printf("good_matches: %d\n", num);
//
//                    waitKey(1);
//
//                    currentROIs.push_back(pair<Rect, Mat>(r0,imageROI));
//
//                }
//            }
//        }
//    }
//
//    return 0;
//}