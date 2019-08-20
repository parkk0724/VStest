// 03Matrix.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cMatrix.h"


int main()
{
	int nMatDimension;
	cout << "행렬 차수를 입력하시오 : ";
	cin >> nMatDimension;

	cMatrix mat1(nMatDimension);
	mat1 = cMatrix::Identity(nMatDimension);

	for (int i = 0; i < nMatDimension; ++i)
	{
		for (int j = 0; j < nMatDimension; ++j)
		{
			mat1[i][j] = (rand() % 1000) / 100.0f;
		}
	}

	mat1.Print();

	// >> : 역 행렬 확인
	float fDet = 0.0f;
	cMatrix matInv = mat1.Inverse(fDet);
	cout << " 역행렬 : " << endl;
	matInv.Print();

	cout << " 역행렬 확인 : " << endl;
	(matInv * mat1).Print();
	// << :

    return 0;
}

