#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <fstream>				//����x�s
#include <vector>				//�ʺA�x�}
#include <string>				//�r��
#include <algorithm>			//�򥻺t��k
#include <omp.h>				//����B�z
#include <math.h>				//math�Ÿ��B��
//#include <Eigen/Dense>	//�S�x��

using namespace std;
using namespace cv;
//using namespace Eigen;

//***		�x�}�]�w		***//
int num = 5;						//�S�x�I�Ӽ�   4���I(�կȥ|�Ө�)
int m = 2 * num;					//��
int n = 9;							//�C	
int k = 9;							//rank=��
vector<vector<long double> > A;		//Input		A*h=0
vector<vector<long double> > B;		//Input		A*h=0
vector<vector<long double> > H;		//Output	
vector<vector<long double> > H2;	//Output
vector<vector<long double> > U;		//U�O�@��(m,m)���x�}
vector<long double> D;				//D�O�@��(m,n)��Diagonal Matrix�]�﨤�}�^  ���u�����﨤�u���S�x�� 
vector<vector<long double> > V;		//V�O�@��(n,n)���x�}
vector<vector<long double> > V2;	//V�O�@��(n,n)���x�}

//***		Figure file			***//
string left_pic = "left.JPG";
string right_pic = "right.jpg";
//Mat left_img = imread(left_pic, IMREAD_COLOR);	//�}���Ӥ�`12	D
//Mat right_img = imread(right_pic, IMREAD_COLOR);	//�}�k�Ӥ�
Mat left_img;	//�}���Ӥ�`12	D
Mat right_img ;	//�}�k�Ӥ�
Mat l_A4 = Mat(1754, 1240, CV_8U);
Mat r_A4 = Mat(1754, 1240, CV_8U);
Mat A4 = Mat(1754, 1240, CV_8U);
int CC, DD;
int test1 = 0;
int test2 = 0;
//***		Figure file			***//
//	�}��HSV�G�Ȥ�
Mat left_hsv;									//HSV
Mat left_hsv_part01;							//�զX01	�D�n�S�x
Mat left_hsv_part02;							//�զX02	��t�S�x													
Mat left_2b_img;
Mat left_paper_img;

//	�}�kHSV�Gleft_2b_img�Ȥ�
Mat right_hsv;									//HSV
Mat right_hsv_part01;							//�զX01	�D�n�S�x
Mat right_hsv_part02;							//�զX02	��t�S�x	
Mat right_2b_img;								//HSV
Mat right_paper_img;

// HSV�Ѽ�
int  H_upper_01 = 92, H_lower_01 = 0;			//H ��m����range  0~180
int  H_upper_02 = 180, H_lower_02 = 120;
int  H_upper_p = 180, H_lower_p = 0;			//H �կ�
int  S_upper_01 = 255, S_lower_01 = 0;			//S ���M����range  0~255
int  S_upper_02 = 255, S_lower_02 = 0;
int  S_upper_p = 30, S_lower_p = 0;			//S �կ�
int  V_upper_01 = 100, V_lower_01 = 0;			//V �G�פ���range  0~255
int  V_upper_02 = 100, V_lower_02 = 0;
int  V_upper_p = 255, V_lower_p = 100;		//V �կ�

//***		every point		***//		
//������
long double mean_r, mean_l;
long double mean_r_x, mean_r_y, mean_l_x, mean_l_y;

//�S�x�I����
vector<long double> l_x = { 935, 2250,1030,  2605,0 };	//���䪺�I
vector<long double> l_y = { 422,   498,2619, 2437,0 };
vector<long double> l_z = { 1,    1,	   1,    1,1 };
vector<long double> r_x = { 1101, 2113, 874,1981,  0 };	//�k�䪺�I
vector<long double> r_y = { 796,  601, 2436,2602, 0 };
vector<long double> r_z = { 1,    1,	   1,	 1,1 };
vector<long double> A4_x = { 0, 1240,	   0,  1240, 620 };	//��v���I
vector<long double> A4_y = { 0,    0, 1754,    1754, 877 };
vector<long double> A4_z = { 1,    1,	   1,	 1,1 };
vector<long double> l_lenght = l_x;		//XY����
vector<long double> r_lenght = l_y;

vector<vector<long double> > l_T;		//�ؤo�ഫ
vector<vector<long double> > r_T;		//�ؤo�ഫ

//***		SVD�Ѽ�		***//	
const int MAX_ITER = 200;								//���N����
const long double error_gate = 0.000000000000000001;	//�̤p�~�t(�p�G�Ӥj  �S�x�ȷ|��

//����B�z
int tid;
double R01 = 0, R02 = 0;
float X_min = 0;
float Y_min = 0;
float X_max = 0;
float Y_max = 0;

//***		���տ�J�P��X		***//
vector<long double>	 in_point = { 0,  0,    0 };				//�ഫ�e
vector<long double> out_point = { 0,	   0,         0 };		//�ഫ��