#pragma once
#include "Header.h"


//***		標準化(正規化)		***//	
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
inline long double normalize2(vector<long double> a) {
	long double sum = 0;
	int n = a.size();
	for (int i = 0; i < n; i++)
		sum += a[i];
	return sum / n;
}

//***		XY距離		***//	
inline std::vector<long double> get_lenght(vector<long double> x, vector<long double> y, long double x_mean, long double y_mean) {
	vector<long double> ans = x;
	int n = x.size();
	for (int i = 0; i < n; i++)
		ans[i] = sqrt(pow(x[i] - x_mean, 2) + pow(y[i] - y_mean, 2));		 //開更號(X^2+Y^2)  
	return ans;
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

//***		取四大點		***//	
inline long double four_point_01(long double &ii, long double &jj) {
	for (int i = 0; i < right_img.rows; i++) {
		int j = i * R01;
		ii = 0;
		jj = 0;
		while (j >= 0) {
			jj = j;
			if (right_paper_img.at<uchar>(ii, jj) == 255) {
				r_y[0] = ii;
				r_x[0] = jj;
				return 0;
			}
			j = j - R01;
			ii++;
		}
	}

}
inline long double four_point_02(long double &ii, long double &jj) {
	for (int i = 0; i < right_img.rows; i++) {
		int j = i * R01;
		ii = right_img.rows;
		jj = 0;
		while (j >= 0) {
			jj = j;
			if (right_paper_img.at<uchar>(ii - 1, jj) == 255) {
				r_y[2] = ii - 1;
				r_x[2] = jj;
				return 0;
			}
			j = j - R01;
			ii--;
		}
	}

}
inline long double four_point_03(long double &ii, long double &jj) {
	for (int i = 0; i < right_img.rows; i++) {
		int j = right_img.cols - i * R01;
		ii = right_img.rows;
		jj = 0;
		while (j <= right_img.cols) {
			jj = j;
			if (right_paper_img.at<uchar>(ii - 1, jj - 1) == 255) {
				r_y[3] = ii - 1;
				r_x[3] = jj - 1;

				return 0;
			}
			j = j + R01;
			ii--;
		}
	}

}
inline long double four_point_04(long double &ii, long double &jj) {
	for (int i = 0; i < right_img.rows; i++) {
		int j = right_img.cols - i * R01;
		ii = 0;
		jj = 0;
		while (j <= right_img.cols) {
			jj = j;
			if (right_paper_img.at<uchar>(ii, jj - 1) == 255) {
				r_y[1] = ii;
				r_x[1] = jj - 1;
				return 0;
			}
			j = j + R01;
			ii++;
		}
	}

}
inline long double four_point_11(long double &ii, long double &jj) {
	for (int i = 0; i < left_img.rows; i++) {
		int j = i * R01;
		ii = 0;
		jj = 0;
		while (j >= 0) {
			jj = j;
			if (left_paper_img.at<uchar>(ii, jj) == 255) {
				l_y[0] = ii;
				l_x[0] = jj;
				return 0;
			}
			j = j - R01;
			ii++;
		}
	}

}
inline long double four_point_12(long double &ii, long double &jj) {

	for (int i = 0; i < left_img.rows; i++) {
		int j = i * R01;
		ii = left_img.rows;
		jj = 0;
		while (j >= 0) {
			jj = j;
			if (left_paper_img.at<uchar>(ii - 1, jj) == 255) {
				l_y[2] = ii - 1;
				l_x[2] = jj;
				return 0;
			}
			j = j - R01;
			ii--;
		}
	}

}
inline long double four_point_13(long double &ii, long double &jj) {
	for (int i = 0; i < left_img.rows; i++) {
		int j = left_img.cols - i * R01;
		ii = left_img.rows;
		jj = 0;
		while (j <= left_img.cols) {
			jj = j;
			if (left_paper_img.at<uchar>(ii - 1, jj - 1) == 255) {
				l_y[3] = ii - 1;
				l_x[3] = jj - 1;

				return 0;
			}
			j = j + R01;
			ii--;
		}
	}

}
inline long double four_point_14(long double &ii, long double &jj) {
	for (int i = 0; i < left_img.rows; i++) {
		int j = left_img.cols - i * R01;
		ii = 0;
		jj = 0;
		while (j <= left_img.cols) {
			jj = j;
			if (left_paper_img.at<uchar>(ii, jj - 1) == 255) {
				l_y[1] = ii;
				l_x[1] = jj - 1;
				return 0;
			}
			j = j + R01;
			ii++;
		}
	}

}

//***		SVD		***//	
bool Used_SVD(vector<vector<long double> > A_SVD, int K_SVD, vector<vector<long double> > &U_SVD, vector<long double> &D_SVD, vector<vector<long double> > &V_SVD) {
	int M = 2 * num;
	int N = n;

	//左右向量定義 (左向量計算U、右向量計算V)
	long double *Alpha = new long double[M];
	long double *Beta = new long double[N];
	long double *temp_Alpha = new long double[M];	 //temp_Alpha向量用于迭帶運算
	long double *temp_Beta = new long double[N];
	int col = 0;

	for (int col = 0; col < K_SVD; col++) {
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
			memset(temp_Beta, 0, sizeof(double)*N);

			/////////////////////////////  V  //////////////////////////////////////
			//生成右迭代向量β_next(1×N)
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					temp_Beta[j] += Alpha[i] * A_SVD[i][j];			//向量β_next(1×N)=向量α(1×M)×A(M×N)矩阵疊加，透過隨機向量來取得
			r = normalize(temp_Beta, N);						//把β_next 進行標準化			
			if (r < error_gate)									//如果標準化<誤差則直接跳出 
				break;											//如果範圍太小(A矩陣或

			//β_next = V與β_next 進行正交運算
			for (int i = 0; i < col; i++)
				orthogonal(&V_SVD[i][0], temp_Beta, N);			//與右矩陣K X V正交，正交化得到β'_next
			normalize(temp_Beta, N);							//單位化β'_next(旋轉過後)

			////////////////////////////////  U  ///////////////////////////////////
			//生成右迭代向量α_next(1×M)			
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					temp_Alpha[i] += temp_Beta[j] * A_SVD[i][j];	//向量α_next(1×M)= A(M×N)×β_next'(N×1)疊加
			r = normalize(temp_Alpha, M);						//把α_next 進行標準化	
			if (r < error_gate)								    //如果標準化<誤差則直接跳出 
				break;

			//α_next = U與α_next 進行正交運算
			for (int i = 0; i < col; i++)
				orthogonal(&U_SVD[i][0], temp_Alpha, M);		//與左矩陣M X K正交，正交化得到α'_next
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
		if (r >= error_gate) {										//若向量的模長(特徵向量對角線以外的值旁邊的數)>error_gate
			D_SVD[col] = r;											//D: r=A矩陣奇異值
			memcpy((char *)&U_SVD[col][0], Alpha, sizeof(double)*M);//U
			memcpy((char *)&V_SVD[col][0], Beta, sizeof(double)*N); //V  (我們只需要這一項)
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

/***************************************  主程式  ********************************************/
namespace WindowsApplication1
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;


	protected:



	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(146, 488);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 44);
			this->button1->TabIndex = 0;
			this->button1->Text = L"開啟圖片";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(25, 53);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(373, 400);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(439, 53);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(373, 400);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 3;
			this->pictureBox2->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(560, 488);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 44);
			this->button2->TabIndex = 2;
			this->button2->Text = L"開啟圖片";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label1->Location = System::Drawing::Point(434, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(93, 27);
			this->label1->TabIndex = 4;
			this->label1->Text = L"左圖片";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label2->Location = System::Drawing::Point(29, 13);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(93, 27);
			this->label2->TabIndex = 5;
			this->label2->Text = L"右圖片";
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(851, 53);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(373, 400);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 6;
			this->pictureBox3->TabStop = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label3->Location = System::Drawing::Point(920, 560);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(46, 27);
			this->label3->TabIndex = 7;
			this->label3->Text = L"長:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label4->Location = System::Drawing::Point(920, 589);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(46, 27);
			this->label4->TabIndex = 8;
			this->label4->Text = L"寬:";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(997, 488);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(107, 44);
			this->button3->TabIndex = 9;
			this->button3->Text = L"開始計算";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label5->Location = System::Drawing::Point(956, 589);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(25, 27);
			this->label5->TabIndex = 11;
			this->label5->Text = L"0";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label6->Location = System::Drawing::Point(956, 560);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(25, 27);
			this->label6->TabIndex = 10;
			this->label6->Text = L"0";
			this->label6->Click += gcnew System::EventHandler(this, &MyForm::label6_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label7->Location = System::Drawing::Point(1075, 589);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(43, 27);
			this->label7->TabIndex = 13;
			this->label7->Text = L"cm";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label8->Location = System::Drawing::Point(1075, 560);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(43, 27);
			this->label8->TabIndex = 12;
			this->label8->Text = L"cm";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label9->Location = System::Drawing::Point(847, 13);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(120, 27);
			this->label9->TabIndex = 14;
			this->label9->Text = L"成果圖片";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1285, 625);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		//宣告點陣圖的格式 
		Bitmap^ image1;
		//new一個新的openFileDialog1開啟檔案
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		//設定Filter，用以限定使用者開啟的檔案
		openFileDialog1->Filter = "JPG圖 (*.jpg)| *.jpg| All files (*.*)| *.*";
		//預設檔案名稱為空值
		openFileDialog1->FileName = "";
		//設定跳出選擇視窗的標題名稱
		openFileDialog1->Title = "載入影像";
		//設定Filter選擇模式(依照Filter數，如本例選擇1表示起始出現的為點陣圖，選擇2表示All filts)
	    openFileDialog1->FilterIndex = 1;


		//跳出檔案選擇視窗(ShowDialog)，並且如果使用者點選檔案，並且檔案名稱超過0個字元，則判斷是為True，進入處理程序
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0)
		{
			//將選取的檔案讀取並且存至Image1
			image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));
			//將影像顯示在pictureBox1
			pictureBox1->Image = image1;
			const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName)).ToPointer();
			string path = chars;
			left_img = imread(path, CV_LOAD_IMAGE_COLOR);
			test1 = 1;
		}

	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		Bitmap^ image1;
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->Filter = "JPG圖 (*.jpg)| *.jpg| All files (*.*)| *.*";
		openFileDialog1->FileName = "";
		openFileDialog1->Title = "載入影像";
		openFileDialog1->FilterIndex = 1;
		std::string path;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0)
		{
			image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));
			pictureBox2->Image = image1;
			System::Runtime::InteropServices::Marshal::StringToCoTaskMemUni(openFileDialog1->FileName);
			//path = openFileDialog1->FileName;
			//left_img = imread(path, CV_LOAD_IMAGE_COLOR);
			const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName)).ToPointer();
			string path = chars;
			right_img = imread(path, CV_LOAD_IMAGE_COLOR);
			test2 = 1;
		}
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		if (test2==1&test1==1){	//有圖片的時候

			//長寬比例尺
			R01 = right_img.rows / right_img.cols;
			R02 = right_img.cols / right_img.rows;

			// 找白紙的四個角
			cvtColor(left_img, left_hsv, CV_RGB2HSV);		//RGB to HSV
			cvtColor(right_img, right_hsv, CV_RGB2HSV);		//RGB to HSV

			inRange(left_hsv, Scalar(H_lower_p, S_lower_p, V_lower_p), Scalar(H_upper_p, S_upper_p, V_upper_p), left_paper_img);
			inRange(right_hsv, Scalar(H_lower_p, S_lower_p, V_lower_p), Scalar(H_upper_p, S_upper_p, V_upper_p), right_paper_img);

			cv::Canny(left_paper_img, left_paper_img, 125, 250);			// Canny邊緣檢測
			threshold(left_paper_img, left_paper_img, 128, 255, THRESH_BINARY);

			cv::Canny(right_paper_img, right_paper_img, 125, 250);			// Canny邊緣檢測
			threshold(right_paper_img, right_paper_img, 128, 255, THRESH_BINARY);

			//找四個點
			four_point_01(r_y[0], r_x[0]);
			four_point_02(r_y[2], r_x[2]);
			four_point_03(r_y[3], r_x[3]);
			four_point_04(r_y[1], r_x[1]);
			r_x[4] = (r_x[0] + r_x[1] + r_x[2] + r_x[3]) / 4;
			r_y[4] = (r_y[0] + r_y[1] + r_y[2] + r_y[3]) / 4;
			four_point_11(l_y[0], l_x[0]);
			four_point_12(l_y[2], l_x[2]);
			four_point_13(l_y[3], l_x[3]);
			four_point_14(l_y[1], l_x[1]);
			l_x[4] = (l_x[0] + l_x[1] + l_x[2] + l_x[3]) / 4;
			l_y[4] = (l_y[0] + l_y[1] + l_y[2] + l_y[3]) / 4;

			////***		正規化		***//
			//// 取平均
			mean_l_x = normalize2(l_x);
			mean_l_y = normalize2(l_y);
			mean_r_x = normalize2(r_x);
			mean_r_y = normalize2(r_y);

			////// 取絕對長度
			l_lenght = get_lenght(l_x, l_y, mean_l_x, mean_l_y);	//取長度
			r_lenght = get_lenght(r_x, r_y, mean_r_x, mean_r_y);
			mean_l = normalize2(l_lenght);							//總平均
			mean_r = normalize2(r_lenght);


			//***		定義A矩陣內容		***//
			for (int i = 0; i < num; i++) {
				A[2 * i][0] = 0;					A[2 * i][1] = 0;					A[2 * i][2] = 0;
				A[2 * i][3] = -A4_z[i] * l_x[i];	A[2 * i][4] = -A4_z[i] * l_y[i];	A[2 * i][5] = -A4_z[i] * l_z[i];
				A[2 * i][6] = A4_y[i] * l_x[i];		A[2 * i][7] = A4_y[i] * l_y[i];		A[2 * i][8] = A4_y[i] * l_z[i];

				A[2 * i + 1][0] = A4_z[i] * l_x[i];	A[2 * i + 1][1] = A4_z[i] * l_y[i];	A[2 * i + 1][2] = A4_z[i] * l_z[i];
				A[2 * i + 1][3] = 0;				A[2 * i + 1][4] = 0;				A[2 * i + 1][5] = 0;
				A[2 * i + 1][6] = -A4_x[i] * l_x[i]; A[2 * i + 1][7] = -A4_x[i] * l_y[i]; A[2 * i + 1][8] = -A4_x[i] * l_z[i];
			}

			for (int i = 0; i < num; i++) {
				B[2 * i][0] = 0;					B[2 * i][1] = 0;					B[2 * i][2] = 0;
				B[2 * i][3] = -A4_z[i] * r_x[i];	B[2 * i][4] = -A4_z[i] * r_y[i];	B[2 * i][5] = -A4_z[i] * r_z[i];
				B[2 * i][6] = A4_y[i] * r_x[i];		B[2 * i][7] = A4_y[i] * r_y[i];		B[2 * i][8] = A4_y[i] * r_z[i];

				B[2 * i + 1][0] = A4_z[i] * r_x[i];	B[2 * i + 1][1] = A4_z[i] * r_y[i];	B[2 * i + 1][2] = A4_z[i] * r_z[i];
				B[2 * i + 1][3] = 0;				B[2 * i + 1][4] = 0;				B[2 * i + 1][5] = 0;
				B[2 * i + 1][6] = -A4_x[i] * r_x[i]; B[2 * i + 1][7] = -A4_x[i] * r_y[i]; B[2 * i + 1][8] = -A4_x[i] * r_z[i];
			}
			//***		SVD			***//
			int ret = Used_SVD(A, k, U, D, V);
			//***	  輸出H矩陣	  ***//
			for (int j = 0; j < 3; j++) {
				H[j][0] = V[V.size() - 1][j] / V[V.size() - 1][V[0].size() - 1];
				H[j][1] = V[V.size() - 1][j + 3] / V[V.size() - 1][V[0].size() - 1];
				H[j][2] = V[V.size() - 1][j + 6] / V[V.size() - 1][V[0].size() - 1];
			}

			A.clear();

			V.clear();
			V2.resize(k);							// K X N
			for (int i = 0; i < k; i++)
				V2[i].resize(n, 0);

			int ret2 = Used_SVD(B, k, U, D, V2);


			//***	  輸出H矩陣	  ***//
			for (int j = 0; j < 3; j++) {
				H2[j][0] = V2[V2.size() - 1][j] / V2[V2.size() - 1][V2[0].size() - 1];
				H2[j][1] = V2[V2.size() - 1][j + 3] / V2[V2.size() - 1][V2[0].size() - 1];
				H2[j][2] = V2[V2.size() - 1][j + 6] / V2[V2.size() - 1][V2[0].size() - 1];
			}
			U.clear();	//釋放
			D.clear();
			V.clear();
			V2.clear();
			//***		HSV  二值化			***//
			inRange(left_hsv, Scalar(H_lower_01, S_lower_01, V_lower_01), Scalar(H_upper_01, S_upper_01, V_upper_01), left_hsv_part01);	//part_01 二值化：h值介於0~10 & s值介於100~255 & v值介於120~255	
			inRange(left_hsv, Scalar(H_lower_02, S_lower_02, V_lower_02), Scalar(H_upper_02, S_upper_02, V_upper_02), left_hsv_part02);	//part_02 二值化：h值介於170~180 & s值介於100~255 & v值介於120~255	
			left_2b_img = left_hsv_part01 + left_hsv_part02;						//將原圖片經由遮罩過濾後，得到結果dst

			inRange(right_hsv, Scalar(H_lower_01, S_lower_01, V_lower_01), Scalar(H_upper_01, S_upper_01, V_upper_01), right_hsv_part01);//part_01 二值化：h值介於0~10 & s值介於100~255 & v值介於120~255	
			inRange(right_hsv, Scalar(H_lower_02, S_lower_02, V_lower_02), Scalar(H_upper_02, S_upper_02, V_upper_02), right_hsv_part02);//part_02 二值化：h值介於170~180 & s值介於100~255 & v值介於120~255	
			right_2b_img = right_hsv_part01 + right_hsv_part02;						//將原圖片經由遮罩過濾後，得到結果dst


			//***		比特徵值範圍大小(只做這個範圍內的DTL)			***//


			//***		代入圖形中的座標點			***//
			for (int nor_x = 0; nor_x < right_img.rows; nor_x++) {						//扣除絕對邊界，減少運算量
				for (int nor_y = 0; nor_y < right_img.cols; nor_y++) {
					if (right_2b_img.at<uchar>(nor_x, nor_y) == 255) {				//取顏色
						CC = right_2b_img.at<uchar>(nor_x, nor_y);

						//////***		矩陣相乘			***//
						in_point[0] = nor_y;// (nor_y - mean_r_y)*1.414 / mean_r;
						in_point[1] = nor_x; // (nor_x - mean_r_x)*1.414 / mean_r;
						in_point[2] = 1;		//r_01定義
						#pragma omp parallel for  schedule(static)
						for (int R = 0; R < 3; R++) {
							out_point[R] = 0;
							for (int T = 0; T < 3; T++)
								out_point[R] += H2[T][R] * in_point[T];					//矩陣相乘
						}


						//////****     normalization     ****//////
						if (out_point[out_point.size() - 1] != 0) {
							for (int R = 0; R < 3; R++)									//運算
								out_point[R] = out_point[R] / out_point[out_point.size() - 1];

							if (out_point[1] >= 0 && out_point[1] <= r_A4.rows && out_point[0] >= 0 && out_point[0] <= r_A4.cols) {			// 範圍判斷		
								r_A4.at<uchar>(out_point[1], out_point[0]) = CC;
							}
						}
					}
				}
			}
			///*		l_x[i] = (l_x[i] - mean_l_x)*1.414 / mean_l;

			for (int nor_x = 0; nor_x < left_img.rows; nor_x++) {						//扣除絕對邊界，減少運算量
				for (int nor_y = 0; nor_y < left_img.cols; nor_y++) {
					if (left_2b_img.at<uchar>(nor_x, nor_y) == 255) {				//取顏色
						DD = left_2b_img.at<uchar>(nor_x, nor_y);
						//////***		矩陣相乘			***//		

						in_point[0] = nor_y;// (nor_y - mean_l_y)*1.414 / mean_l;
						in_point[1] = nor_x;// (nor_x - mean_l_x)*1.414 / mean_l;
						in_point[2] = 1;		//r_01定義
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
							if (out_point[1] >= 0 && out_point[1] <= l_A4.rows && out_point[0] >= 0 && out_point[0] <= l_A4.cols) {			// 範圍判斷		
								l_A4.at<uchar>(out_point[1], out_point[0]) = DD;
							}
						}
					}
				}
			}
			for (int nor_x = 0; nor_x < A4.cols; nor_x++) {						//扣除絕對邊界，減少運算量
				for (int nor_y = 0; nor_y < A4.rows; nor_y++) {
					if (l_A4.at<uchar>(nor_y, nor_x) == 255 && r_A4.at<uchar>(nor_y, nor_x) == 255) {
						A4.at<uchar>(nor_y, nor_x) = 255;
						if (nor_x > X_max)
							X_max = nor_x;
						if (nor_x < X_min)
							X_min = nor_x;
						if (nor_y > Y_max)
							Y_max = nor_y;
						if (nor_y < Y_min)
							Y_min = nor_y;
					}
				}
			}

			//pictureBox2->r_A4;
			this->label5->Text = L"" + X_max / 59;
			this->label6->Text = L"" + Y_max / 59;
			////////***		顯示圖片		***//////
			//addWeighted(orig_img, -1, out_img, 1, 0, compare_result);			//圖像相減
			imwrite("sol_left_A4.jpg ", l_A4);	//l_A4  left_2b_img  left_hsv left_paper_img
			imwrite("sol_right_A4.jpg ", r_A4);				//r_A4
			imwrite("sol_A4.jpg ", A4);

			Bitmap^ image_L;
			Bitmap^ image_R;
			Bitmap^ image_Sol;
			OpenFileDialog^ openFileDialog_L = gcnew OpenFileDialog;
			OpenFileDialog^ openFileDialog_R = gcnew OpenFileDialog;
			OpenFileDialog^ openFileDialog_Sol = gcnew OpenFileDialog;
			openFileDialog_L->FileName = "sol_left_A4.jpg";
			openFileDialog_R->FileName = "sol_right_A4.jpg";
			openFileDialog_Sol->FileName = "sol_A4.jpg";

				image_L = safe_cast<Bitmap^>(Image::FromFile(openFileDialog_L->FileName));
				pictureBox1->Image = image_L;
				System::Runtime::InteropServices::Marshal::StringToCoTaskMemUni(openFileDialog_L->FileName);

				image_R = safe_cast<Bitmap^>(Image::FromFile(openFileDialog_R->FileName));
				pictureBox2->Image = image_R;
				System::Runtime::InteropServices::Marshal::StringToCoTaskMemUni(openFileDialog_R->FileName);

				image_Sol = safe_cast<Bitmap^>(Image::FromFile(openFileDialog_Sol->FileName));
				pictureBox3->Image = image_Sol;
				System::Runtime::InteropServices::Marshal::StringToCoTaskMemUni(openFileDialog_Sol->FileName);
		}
		else {
		MessageBox::Show("請開啟圖片");
}
	}
private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}