#include "MyForm.h"
#include <iostream>

using namespace WindowsApplication1;

[STAThreadAttribute]

int main(void)
{
	//true == 1, false == 0
	// 建立任何控制項之前，先啟用 Windows XP 視覺化效果
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);



	//***		初始化		***//
	U.clear();
	D.clear();
	V.clear();
	V2.clear();
	H.clear();
	H2.clear();
	l_T.clear();
	r_T.clear();

	//***		矩陣大小定義		***//
	A.resize(m);							//重新定義A大小
	for (int i = 0; i < m; i++)
		A[i].resize(n);

	B.resize(m);							//重新定義B大小
	for (int i = 0; i < m; i++)
		B[i].resize(n);

	U.resize(k);							// M X K
	for (int i = 0; i < k; i++)
		U[i].resize(m, 0);

	V.resize(k);							// K X N
	for (int i = 0; i < k; i++)
		V[i].resize(n, 0);


	H.resize(k / 3);						// 3 X 3
	for (int i = 0; i < k / 3; i++)
		H[i].resize(n / 3, 0);

	H2.resize(k / 3);						// 3 X 3
	for (int i = 0; i < k / 3; i++)
		H2[i].resize(n / 3, 0);

	D.resize(k, 0);							// K X K(只看對角線)

	l_T.resize(k / 3);						// 3 X 3	
	for (int i = 0; i < k / 3; i++)
		l_T[i].resize(n / 3, 0);

	r_T.resize(k / 3);						// 3 X 3
	for (int i = 0; i < k / 3; i++)
		r_T[i].resize(n / 3, 0);

	// 建立主視窗並執行
	Application::Run(gcnew MyForm());

	cvWaitKey(0);
	return 0;			//結束程式執行，並回傳 0 代表程式執行正常無異狀。
}

