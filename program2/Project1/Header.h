#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>
#include <omp.h>
//#include <Eigen/Dense>

using namespace std;
using namespace cv;
//using namespace Eigen;

//***		Figure file			***//
string true_pic = "test.JPG";
string orig_pic = "GroundTruth.jpg";
Mat true_img = imread(true_pic);
Mat orig_img = imread(orig_pic);
Mat out_img(orig_img.rows, orig_img.cols, CV_8UC3);
Mat compare_result(orig_img.rows, orig_img.cols, CV_8UC3);

//***		every point		***//		
int num = 5;																		//特徵點個數   12個點
long double mean_r_x, mean_r_y, mean_t_x, mean_t_y;									//取平均
vector<int> r_x = { 936,  647, 2610, 2815, 1570 ,1490,	831, 2640,2265};			//特徵點分布
vector<int> r_y = { 749, 2641, 2946,  158, 1533 ,2273, 1727, 1429,1825};
vector<int> r_z = { 1,      1,	  1,	1,    1,    1,	  1,    1,   1};
vector<int> t_x = { 0,      0, 1023, 1023,  504,  509,	 35,  992, 861};
vector<int> t_y = { 0,	  767,  767,    0,  366, 615,	412,  368, 475};
vector<int> t_z = { 1,	    1,	  1,    1,    1,   1,	  1,    1,   1};

int X_min = r_x[0];
int Y_min = r_y[0];
int X_max=  r_x[0];
int Y_max = r_y[0];

int tid;		//平行處理

uchar b, g, r;
Vec3b pix;
//***		輸入與輸出		***//
vector<int>		in_point = { r_x[4],  r_y[4],    r_z[0] };	//轉換前
vector<double> out_point = { 0,	   0,         0 };			//轉換後