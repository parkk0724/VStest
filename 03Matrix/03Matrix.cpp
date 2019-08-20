// 03Matrix.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "cMatrix.h"


int main()
{
	int nMatDimension;
	cout << "��� ������ �Է��Ͻÿ� : ";
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

	// >> : �� ��� Ȯ��
	float fDet = 0.0f;
	cMatrix matInv = mat1.Inverse(fDet);
	cout << " ����� : " << endl;
	matInv.Print();

	cout << " ����� Ȯ�� : " << endl;
	(matInv * mat1).Print();
	// << :

    return 0;
}

