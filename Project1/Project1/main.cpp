
#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <fstream> 
#include <vector>
#include <string>
using namespace cv;
using namespace std;

// File name
string filename = "uname.xyz";
string picname  = "Monk";
ofstream file;				//要改檔名要改這裡

// Pic name
const char* Bird[11] = { "Bird/01.bmp","Bird/02.bmp","Bird/03.bmp","Bird/04.bmp","Bird/05.bmp","Bird/06.bmp","Bird/07.bmp","Bird/08.bmp","Bird/09.bmp","Bird/10.bmp","Bird/11.bmp" };
const char* Last[11] = { "Last/01.bmp","Last/02.bmp","Last/03.bmp","Last/04.bmp","Last/05.bmp","Last/06.bmp","Last/07.bmp","Last/08.bmp","Last/09.bmp","Last/10.bmp","Last/11.bmp" };
const char* Monk[11] = { "Monk/01.bmp","Monk/02.bmp","Monk/03.bmp","Monk/04.bmp","Monk/05.bmp","Monk/06.bmp","Monk/07.bmp","Monk/08.bmp","Monk/09.bmp","Monk/10.bmp","Monk/11.bmp" };
const char* Teap[11] = { "Teap/01.bmp","Teap/02.bmp","Teap/03.bmp","Teap/04.bmp","Teap/05.bmp","Teap/06.bmp","Teap/07.bmp","Teap/08.bmp","Teap/09.bmp","Teap/10.bmp","Teap/11.bmp" };


//Figure file
Mat img = imread(Last[0], CV_8U);
Mat temp;
vector<Mat> img_all(11);								//imshow("顯示圖像", img);

														// Matrix
Mat Instrisic    = (Mat_<double>(3, 3) << 722.481995,	   0.0,     399.0,      0.0, 722.481934,     311.0,       0.0,       0.0,      1.0);
Mat Extrinsic_01 = (Mat_<double>(3, 4) <<   0.508468,  0.860935, -0.015857, 3.932282, -0.101237,  0.041482, -0.994003, 21.303495, -0.855111,  0.507022,  0.108232,  88.085114);
Mat Extrinsic_02 = (Mat_<double>(3, 4) <<   0.054555,  0.997525,  0.044349,-0.396882, -0.129876,  0.051127, -0.990217, 21.030863, -0.990031,  0.048262,  0.132325,  86.551529);
Mat Extrinsic_03 = (Mat_<double>(3, 4) <<  -0.483178,  0.864219,  0.140232,-6.133193, -0.118992,  0.093863, -0.988454, 21.073915, -0.867401, -0.494281,  0.057464,  88.905014);
Mat Extrinsic_04 = (Mat_<double>(3, 4) <<  -0.826707,  0.562054,  0.025509,-3.706015, -0.015798,  0.022133, -0.999636, 22.618803, -0.562411, -0.826804, -0.009437,  89.343170);
Mat Extrinsic_05 = (Mat_<double>(3, 4) <<  -0.920328, -0.386141,  0.062375, 0.837949, -0.102550,  0.084312, -0.991155, 20.728113,  0.377463, -0.918577, -0.117211,  93.253716);
Mat Extrinsic_06 = (Mat_<double>(3, 4) <<  -0.315707, -0.948836, -0.006217, 2.520231, -0.091609,  0.037001, -0.995114, 20.983803,  0.944422, -0.313592, -0.098622,  93.845718);
Mat Extrinsic_07 = (Mat_<double>(3, 4) <<   0.547250, -0.836131, -0.037448,-5.300584, -0.082565, -0.009407, -0.996548, 21.209290,  0.832886,  0.548449, -0.074202,  91.918419);
Mat Extrinsic_08 = (Mat_<double>(3, 4) <<   0.998758, -0.047722, -0.014321, 7.249783, -0.026645, -0.268707, -0.962861, 16.707335,  0.042101,  0.962035, -0.269661, 101.258018);
Mat Extrinsic_09 = (Mat_<double>(3, 4) <<   0.515633,  0.856808,  0.001705, 1.082603,  0.856751, -0.515573, -0.013213,  4.623665, -0.010425,  0.008264, -0.999911, 114.083206);
Mat Extrinsic_10 = (Mat_<double>(3, 4) <<  -0.164361,  0.974144, -0.155012, 2.258266, -0.915024, -0.209267, -0.344892,  8.572358, -0.368429,  0.085148,  0.925748,  76.273094);
Mat Extrinsic_11 = (Mat_<double>(3, 4) <<  -0.053241,  0.998369,  0.020604, 1.405633, -0.737301, -0.053217,  0.673473,-20.414452,  0.673454,  0.020664,  0.738940,  80.795265);
Mat Extrinsic_all[11] = { Extrinsic_01, Extrinsic_02, Extrinsic_03, Extrinsic_04, Extrinsic_05, Extrinsic_06, Extrinsic_07, Extrinsic_08, Extrinsic_09, Extrinsic_10, Extrinsic_11 };
Mat X_world		 = (Mat_<double>(4, 1) << 0, 0, 0, 1);
Mat X_2D		 = (Mat_<double>(3, 1) << 0, 0, 0);



/***********************************************************************************/
/****  Check iteration  ****/
int Check(Mat X_world, int i) {

	// axis point 
	double pic_x = 0, pic_y = 0, pic_z = 0;
	int    nor_x = 0, nor_y = 0, nor_z = 0;
	int    check_num = 0;

	if (i < 2) {

		/**** Formule ****/
		X_2D = Instrisic * (Extrinsic_all[i] * X_world);

		/**** Get 2D XYZ ****/
		pic_x = X_2D.at<double>(0, 0);
		pic_y = X_2D.at<double>(1, 0);
		pic_z = X_2D.at<double>(2, 0);

		/**** normalization ****/
		if (pic_z != 0) {
			nor_x = pic_x / pic_z;
			nor_y = pic_y / pic_z;
			nor_z = pic_z / pic_z;
		}
		else {
			return 0;
		}

		/****  change to int and check white point in 2D  ****/
		if (nor_y > 0 && nor_x > 0 && nor_x < img.cols && nor_y < img.rows) {//check frigure range (X=0 y=0角度之二維點照射過去都是邊 可略)
			//int channels = img_all[i].channels();							 //確認單通道
			check_num = (int)img_all[i].at<uchar>(nor_y, nor_x);			 //圖片一定要用uchar  先用y再用x
			if (check_num == 255) {
				Check(X_world, i + 1);										 //NEXT Iteration
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	else {
		/**** Output ****/						
		//std::cout << "x=" << X_world.at<double>(0, 0) << "\ty=" << X_world.at<double>(1, 0) << "\tz=" << X_world.at<double>(2, 0) <<"\tTT=" << check_num << "\tacount=" << i << std::endl;
		file << " " << X_world.at<double>(0, 0) << " " << X_world.at<double>(1, 0) << " " << X_world.at<double>(2, 0) << std::endl;
		return 0;
	}
};



/***********************************************************************************/
int main(int argc, char const *argv[]) {

	/**** DOS window ****/
	std::cout << ">> Please select input file's name(monkay, bird, teapot or last)" << std::endl;
	std::cout << ">> ";
	std::cin >> picname;
	std::cout << ">> Please keyin the output file name" << std::endl;
	std::cout << ">> ";
	std::cin  >> filename;
	file.open(filename, ios::out);						//openfile

	/**** pic input to vecotr ****/
	if (picname == "Monkey" || picname == "monkey" || picname == "Monk" || picname == "monk") {		
		for (int i = 0; i < 11; ++i)					//要改圖片要改這裡(used vector)
			{img_all[i] = imread(Monk[i], CV_8U);}		
	}else if (picname == "Teapot" || picname == "teapot" || picname == "Teap" || picname == "teap") {
		for (int i = 0; i < 11; ++i)
			{img_all[i] = imread(Teap[i], CV_8U);}
	}else if (picname == "Bird" || picname == "bird" ) {
		for (int i = 0; i < 11; ++i)
			{img_all[i] = imread(Bird[i], CV_8U);}
	}else if (picname == "Last" || picname == "last" ) {
		for (int i = 0; i < 11; ++i)
			{img_all[i] = imread(Last[i], CV_8U);}
	}else {
		std::cout << "Can't find this file's name" << std::endl;
		system("pause");
		return 0;
	}
	std::cout << ">> Waiting..." << std::endl << std::endl << std::endl;

	


	/**** Stereo Vision Loop ****/
	for (int x = -50; x <= 50; ++x) {
		for (int y = -50; y <= 50; ++y) {			
			for (int z = 0; z <= 100; ++z) {

				/**** scan 3D cloud point ****/
				X_world.at<double>(0, 0) = x;
				X_world.at<double>(1, 0) = y;
				X_world.at<double>(2, 0) = z;				

				int i = 0;
				Check(X_world,i);	
			}
		}
	}
	std::cout << " Done!!" << std::endl;
	system("pause");
	//waitKey(0);
	return 0;
}


