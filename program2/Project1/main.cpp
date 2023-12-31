#include "Header.h"

//***		SVD參數		***//	
const int MAX_ITER = 200;								//迭代次數
const long double error_gate = 0.0000000001;			//最小誤差

//***		標準化		***//	
inline double normalize(long double *x, int n) {//在 function 原型前面加上 inline 即可，如此前置處理器就會幫你將函式主體 copy 到呼叫函式的地方
	double r = 0, sq_r = 0;
	for (int i = 0; i < n; i++)					// 每個長度相加
		r += x[i] * x[i];
	sq_r = sqrt(r);								// 統一取開耕號的r

	if (sq_r < error_gate)						//當x的總體長度<error_gate時	
		return 0;
	for (int i = 0; i < n; i++)					//當x的總體長度>error_gate時，將x[i]/|x|，將向量x進行 nirmalizet成為单位向量
		x[i] /= sq_r;
	return sq_r;
}
inline long double normalize2(vector<int> a, int n){
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += a[i];
	return sum / n;
}

//***		正交		***//	
inline void orthogonal(long double *a, long double *b, int n) {	//正交，讓|a|=1
	double r = 0;
	//**  product a*b  **//
	for (int i = 0; i < n; i++)
		r += a[i] * b[i];

	//**  orthogonal vector  **//
	for (int i = 0; i < n; i++)
		b[i] -= r * a[i];
}

//***		SVD		***//	
bool Used_SVD(vector<vector<int> > A, int K, vector<vector<long double> > &U, vector<long double> &D, vector<vector<long double> > &V) {
	int M = 2 * num;
	int N = 9;

	//左右向量定義 (左向量計算U、右向量計算V)
	long double *Alpha = new long double[M];
	long double *Beta  = new long double[N];
	long double *temp_Alpha = new long double[M];	 //temp_Alpha向量用于迭帶運算
	long double *temp_Beta  = new long double[N];
	int col = 0;

	for (int col = 0; col < K; col++) {
		double diff = 1;
		double r = -1;

		//生成向量 α  (比對之後疊加到U矩陣中)
		while (1) {
			for (int i = 0; i < M; i++)						
				Alpha[i] = (float)rand();						//隨機生成一个向量 α(1×M)  並用迭帶一直嘗試逼近正確值
			if (normalize(Alpha, M) > error_gate)				//當向量的絕對長度>error_gate，則完成left_vector向量，跳出loop；
				break;
		}

		//進入迭代
		for (int iter = 0; diff >= error_gate && iter < MAX_ITER; iter++) {

			//分配內存給  左迭代向量α  和右迭代向量β
			memset(temp_Alpha, 0, sizeof(double)*M);
			memset(temp_Beta,  0, sizeof(double)*N);

			/////////////////////////////  V  //////////////////////////////////////
			//生成右迭代向量β_next(1×N)
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					temp_Beta[j] += Alpha[i] * A[i][j];			//向量β_next(1×N)=向量α(1×M)×A(M×N)矩阵疊加，透過隨機向量來取得
			r = normalize(temp_Beta, N);						//把β_next 進行標準化			
			if (r < error_gate)									//如果標準化<誤差則直接跳出 
				break;											//如果範圍太小(A矩陣或

			//β_next = V與β_next 進行正交運算
			for (int i = 0; i < col; i++)
				orthogonal(&V[i][0], temp_Beta, N);				//與右矩陣K X V正交，正交化得到β'_next
			normalize(temp_Beta, N);							//單位化β'_next(旋轉過後)

			////////////////////////////////  U  ///////////////////////////////////
			//生成右迭代向量α_next(1×M)			
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					temp_Alpha[i] += temp_Beta[j] * A[i][j];	//向量α_next(1×M)= A(M×N)×β_next'(N×1)疊加
			r = normalize(temp_Alpha, M);						//把α_next 進行標準化	
			if (r < error_gate)								    //如果標準化<誤差則直接跳出 
				break;

			//α_next = U與α_next 進行正交運算
			for (int i = 0; i < col; i++)
				orthogonal(&U[i][0], temp_Alpha, M);			//與左矩陣M X K正交，正交化得到α'_next
			normalize(temp_Alpha, M);							//單位化α'_next(旋轉過後)

			///////////////////////////////////////////////////////////////////
			//誤差判斷(用來決定是否終止疊代)
			diff = 0;
			for (int i = 0; i < M; i++) {
				double d = temp_Alpha[i] - Alpha[i];			//計算前後兩個迭代向量的差距的平方(並疊加)
				diff += d * d;
			}

			//存放內存     
			memcpy(Alpha, temp_Alpha, sizeof(double)*M);		//α=α'_next		U
			memcpy(Beta, temp_Beta, sizeof(double)*N);			//β=β'_next		V
		}

		///////////////////////////  輸出  ////////////////////////////////////////
		//得到A矩陣之奇異值
		if (r >= error_gate) {									//若向量的模長(特徵向量對角線以外的值旁邊的數)>error_gate
			D[col] = r;											//D: r=A矩陣奇異值
			memcpy((char *)&U[col][0], Alpha, sizeof(double)*M);//U
			memcpy((char *)&V[col][0], Beta, sizeof(double)*N); //V
		}
		else {
			break;
		}
	}

	//清空所有不必要的向量
	delete[] Alpha;
	delete[] temp_Alpha;
	delete[] Beta;
	delete[] temp_Beta;
	return 0;
}

//取最大最小
inline void compare(){
	for (int i = 1; i < r_x.size(); i++)
		if (r_x[i] > X_max)
			X_max = r_x[i];
	for (int i = 1; i < r_x.size(); i++)
		if (r_x[i] < X_min)
			X_min = r_x[i];
	for (int i = 1; i < r_y.size(); i++)
		if (r_y[i] > Y_max)
			Y_max = r_y[i];
	for (int i = 1; i < r_y.size(); i++)
		if (r_y[i] < Y_min)
			Y_min = r_y[i];
}
/***************************************  主程式  ********************************************/
int main(int argc, char const *argv[]) {
	//***		矩陣設定		***//
	int m = 2 * num;					//行
	int n = 9;							//列	
	int k = 9;							//rank=行
	vector<vector<int> > A;				//Input		A*h=0
	vector<vector<long double> > H;		//Output	
	vector<vector<long double> > U;		//U是一個(m,m)的矩陣
	vector<long double> D;				//D是一個(m,n)的Diagonal Matrix（對角陣）  但只有取對角線的特徵值 
	vector<vector<long double> > V;		//V是一個(n,n)的矩陣

	// 初始化 //
	U.clear();
	D.clear();
	V.clear();
	H.clear();

	// 正規化 //
	mean_r_x = normalize2(r_x, r_x.size());
	mean_r_y = normalize2(r_x, r_y.size());
	mean_t_x = normalize2(r_x, t_x.size());
	mean_t_y = normalize2(r_x, t_y.size());

	//***		矩陣大小定義		***//
	A.resize(m);							//重新定義A大小
	for (int i = 0; i < m; i++)
		A[i].resize(n);

	U.resize(k);							// M X K
	for (int i = 0; i < k; i++)
		U[i].resize(m, 0);

	V.resize(k);							// K X N
	for (int i = 0; i < k; i++) 			
		V[i].resize(n, 0);

	H.resize(k / 3);						// 3 X 3
	for (int i = 0; i < k / 3; i++) 		
		H[i].resize(n / 3, 0);

	D.resize(k, 0);							// K X K

	//***		定義矩陣內容		***//
	for (int i = 0; i < num; i++) {
		A[2 * i][0] = 0;					A[2 * i][1] = 0;					A[2 * i][2] = 0;
		A[2 * i][3] = -t_z[i] * r_x[i];		A[2 * i][4] = -t_z[i] * r_y[i];		A[2 * i][5] = -t_z[i] * r_z[i];
		A[2 * i][6] = t_y[i] * r_x[i];		A[2 * i][7] = t_y[i] * r_y[i];		A[2 * i][8] = t_y[i] * r_z[i];

		A[2 * i + 1][0] = t_z[i] * r_x[i];	A[2 * i + 1][1] = t_z[i] * r_y[i];	A[2 * i + 1][2] = t_z[i] * r_z[i];
		A[2 * i + 1][3] = 0;				A[2 * i + 1][4] = 0;				A[2 * i + 1][5] = 0;
		A[2 * i + 1][6] = -t_x[i] * r_x[i];	A[2 * i + 1][7] = -t_x[i] * r_y[i];	A[2 * i + 1][8] = -t_x[i] * r_z[i];
	}

	//***		SVD			***//
	int ret = Used_SVD(A, k, U, D, V);
	
	//***	  輸出H矩陣	  ***//
	for (int j = 0; j < 3; j++) {
		H[j][0] = V[V.size() - 1][j] / V[V.size() - 1][V[0].size() - 1];
		H[j][1] = V[V.size() - 1][j + 3] / V[V.size() - 1][V[0].size() - 1];
		H[j][2] = V[V.size() - 1][j + 6] / V[V.size() - 1][V[0].size() - 1];
	}

	//***		比特徵值範圍大小(只做這個範圍內的DTL)			***//
	compare();

	//***		代入圖形中的座標點			***//
	for (int nor_x = X_min; nor_x < X_max; nor_x++) {						//扣除絕對邊界，減少運算量
		for (int nor_y = Y_min; nor_y < Y_max; nor_y++) {

			b = true_img.at<Vec3b>(nor_y, nor_x)[0];						//取顏色
			g = true_img.at<Vec3b>(nor_y, nor_x)[1];
			r = true_img.at<Vec3b>(nor_y, nor_x)[2];

			//////***		矩陣相乘			***//
			in_point[0] = nor_x, in_point[1] = nor_y, in_point[2] = 1;		//r_01定義
			#pragma omp parallel for  schedule(static)
			for (int R = 0; R < 3; R++) {
				out_point[R] = 0;
				for (int T = 0; T < 3; T++)
					out_point[R] += H[T][R] * in_point[T];					//矩陣相乘
			}

			//////****     normalization     ****//////
			if (out_point[out_point.size() - 1] != 0) {							
				for (int R = 0; R < 3; R++)									//運算
					out_point[R] = out_point[R] / out_point[out_point.size() - 1];
				if (out_point[1] >= 0 && out_point[1] <= orig_img.rows && out_point[0] >= 0 && out_point[0] <= orig_img.cols) {			// 範圍判斷		
					//cout << setw(12) << out_point[1] << setw(12) << out_point[0] << endl;
					out_img.at<Vec3b>(out_point[1], out_point[0])[0] = b;
					out_img.at<Vec3b>(out_point[1], out_point[0])[1] = g;
					out_img.at<Vec3b>(out_point[1], out_point[0])[2] = r;
				}
			}
		}			
	}
	/*
	cout << endl;
	cout << "H=" << endl;
	for (int i = 0; i < H[0].size(); i++) {
		for (int j = 0; j < H.size(); j++) {
			cout << setw(12) << H[j][i] << ' ';
		}
		cout << endl;
	}
	cout << endl;*/
	cout << endl;
	cout << "H=" << endl;
	for (int i = 0; i < H[0].size(); i++) {
		for (int j = 0; j < H.size(); j++) {
			cout << setw(12) << H[j][i] << ' ';
		}
		cout << endl;
	}
	
	//////***		顯示圖片		***//////
	addWeighted(orig_img, -1, out_img, 1, 0, compare_result);			//圖像相減
	cv::namedWindow("Purpose_pic");						  
	cv::imshow("Purpose_pic", orig_img);
	//cv::namedWindow("Output_pic", WINDOW_NORMAL);	
	cv::namedWindow("Output_pic");										//自動調變視窗大小
	cv::imshow("Output_pic", out_img);
	cv::namedWindow("Compare_pic");										//自動調變視窗大小
	cv::imshow("Compare_pic", compare_result);

	//////***		儲存圖片		***//////
	imwrite("M10707307.jpg ", out_img);
	imwrite("M10707307.bmp ", compare_result);
	cvWaitKey(0);
	return 0;
}
