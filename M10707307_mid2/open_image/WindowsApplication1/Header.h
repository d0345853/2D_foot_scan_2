#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <fstream>				//文件儲存
#include <vector>				//動態矩陣
#include <string>				//字串
#include <algorithm>			//基本演算法
#include <omp.h>				//平行處理
#include <math.h>				//math符號運算
//#include <Eigen/Dense>	//特徵值

using namespace std;
using namespace cv;
//using namespace Eigen;

//***		矩陣設定		***//
int num = 5;						//特徵點個數   4個點(白紙四個角)
int m = 2 * num;					//行
int n = 9;							//列	
int k = 9;							//rank=行
vector<vector<long double> > A;		//Input		A*h=0
vector<vector<long double> > B;		//Input		A*h=0
vector<vector<long double> > H;		//Output	
vector<vector<long double> > H2;	//Output
vector<vector<long double> > U;		//U是一個(m,m)的矩陣
vector<long double> D;				//D是一個(m,n)的Diagonal Matrix（對角陣）  但只有取對角線的特徵值 
vector<vector<long double> > V;		//V是一個(n,n)的矩陣
vector<vector<long double> > V2;	//V是一個(n,n)的矩陣

//***		Figure file			***//
string left_pic = "left.JPG";
string right_pic = "right.jpg";
//Mat left_img = imread(left_pic, IMREAD_COLOR);	//腳左照片`12	D
//Mat right_img = imread(right_pic, IMREAD_COLOR);	//腳右照片
Mat left_img;	//腳左照片`12	D
Mat right_img ;	//腳右照片
Mat l_A4 = Mat(1754, 1240, CV_8U);
Mat r_A4 = Mat(1754, 1240, CV_8U);
Mat A4 = Mat(1754, 1240, CV_8U);
int CC, DD;
int test1 = 0;
int test2 = 0;
//***		Figure file			***//
//	腳左HSV二值化
Mat left_hsv;									//HSV
Mat left_hsv_part01;							//組合01	主要特徵
Mat left_hsv_part02;							//組合02	邊緣特徵													
Mat left_2b_img;
Mat left_paper_img;

//	腳右HSV二left_2b_img值化
Mat right_hsv;									//HSV
Mat right_hsv_part01;							//組合01	主要特徵
Mat right_hsv_part02;							//組合02	邊緣特徵	
Mat right_2b_img;								//HSV
Mat right_paper_img;

// HSV參數
int  H_upper_01 = 92, H_lower_01 = 0;			//H 色彩分布range  0~180
int  H_upper_02 = 180, H_lower_02 = 120;
int  H_upper_p = 180, H_lower_p = 0;			//H 白紙
int  S_upper_01 = 255, S_lower_01 = 0;			//S 飽和分布range  0~255
int  S_upper_02 = 255, S_lower_02 = 0;
int  S_upper_p = 30, S_lower_p = 0;			//S 白紙
int  V_upper_01 = 100, V_lower_01 = 0;			//V 亮度分布range  0~255
int  V_upper_02 = 100, V_lower_02 = 0;
int  V_upper_p = 255, V_lower_p = 100;		//V 白紙

//***		every point		***//		
//取平均
long double mean_r, mean_l;
long double mean_r_x, mean_r_y, mean_l_x, mean_l_y;

//特徵點分布
vector<long double> l_x = { 935, 2250,1030,  2605,0 };	//左邊的點
vector<long double> l_y = { 422,   498,2619, 2437,0 };
vector<long double> l_z = { 1,    1,	   1,    1,1 };
vector<long double> r_x = { 1101, 2113, 874,1981,  0 };	//右邊的點
vector<long double> r_y = { 796,  601, 2436,2602, 0 };
vector<long double> r_z = { 1,    1,	   1,	 1,1 };
vector<long double> A4_x = { 0, 1240,	   0,  1240, 620 };	//投影的點
vector<long double> A4_y = { 0,    0, 1754,    1754, 877 };
vector<long double> A4_z = { 1,    1,	   1,	 1,1 };
vector<long double> l_lenght = l_x;		//XY長度
vector<long double> r_lenght = l_y;

vector<vector<long double> > l_T;		//尺寸轉換
vector<vector<long double> > r_T;		//尺寸轉換

//***		SVD參數		***//	
const int MAX_ITER = 200;								//迭代次數
const long double error_gate = 0.000000000000000001;	//最小誤差(如果太大  特徵值會遺失

//平行處理
int tid;
double R01 = 0, R02 = 0;
float X_min = 0;
float Y_min = 0;
float X_max = 0;
float Y_max = 0;

//***		測試輸入與輸出		***//
vector<long double>	 in_point = { 0,  0,    0 };				//轉換前
vector<long double> out_point = { 0,	   0,         0 };		//轉換後