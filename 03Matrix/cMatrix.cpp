#include "stdafx.h"
#include "cMatrix.h"


cMatrix::cMatrix()
{
}


cMatrix::~cMatrix()
{
}

cMatrix::cRow::cRow()
{
}

cMatrix::cRow::cRow(int nDimension)
{
	Resize(nDimension);
}

void cMatrix::cRow::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
}

float & cMatrix::cRow::operator[](int nIndex)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vecData[nIndex];
}

cMatrix::cMatrix(int nDimension)
{
	Resize(nDimension);
}

void cMatrix::Print()
{
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			printf("%8.2f", (*this)[i][j]);
		}
		printf("\n");
	}
}

void cMatrix::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
	for (size_t i = 0; i < nDimension; ++i)
		m_vecData[i].Resize(nDimension);
}

int cMatrix::Dimension()
{
	return (int)m_vecData.size();
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix matRet(nDimension);
	for (int i = 0; i < nDimension; i++)
	{
		for (int j = 0; j < nDimension; j++)
		{
			matRet[i][j] = (i == j) ? 1 : 0;
		}
	}
	return matRet;
}

cMatrix::cRow & cMatrix::operator[](int nIndex)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vecData[nIndex];
}

bool cMatrix::operator==(cMatrix & mat)
{
	float fEpsilon = 0.0001f;
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			if ((*this)[i][j] - fEpsilon > mat[i][j])
				return false;
			if ((*this)[i][j] + fEpsilon < mat[i][j])
				return false;
		}
	}
	return true;
}

bool cMatrix::operator!=(cMatrix & mat)
{
	return !((*this) == mat);
}

cMatrix cMatrix::operator+(cMatrix & mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}

	return matRet;
}

cMatrix cMatrix::operator-(cMatrix & mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}

	return matRet;
}

cMatrix cMatrix::operator*(cMatrix & mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = 0.f;
			for (int k = 0; k < Dimension(); k++)
			{
				matRet[i][j] += ((*this)[i][k] * mat[k][j]);
			}
		}
	}

	return matRet;
}

cMatrix cMatrix::operator*(float f)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] * f;
		}
	}

	return matRet;
}

cMatrix cMatrix::Inverse(OUT float & fDeterminat)
{
	cMatrix matRet = cMatrix::Identity(Dimension());

	fDeterminat = Determinant();
	float fEpsilon = 0.0001f;

	if (-fEpsilon < fDeterminat && fDeterminat < fEpsilon)
	{
		cout << " 역행렬이 존재 하지 않음 " << endl;
		return matRet;
	}

	cMatrix matAdj = Adjoint();

	matRet = matAdj * (1 / fDeterminat);

	return matRet;
}

float cMatrix::Determinant()
{
	if (Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
	}

	float fDeterminant = 0.0f;
	for (int i = 0; i < Dimension(); i++)
	{
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));
	}

	return fDeterminant;
}

cMatrix cMatrix::Adjoint()
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = Cofactor(j, i);
		}
	}

	return matRet;
}

cMatrix cMatrix::Transpose()
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}

	return matRet;
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;
	if ((nRow + nCol) % 2 != 0)
		nConst = -1;

	return nConst * Minor(nRow, nCol);
}

float cMatrix::Minor(int nRow, int nCol)
{
	cMatrix matMinor(Dimension() - 1);

	int nMinorRow = 0;
	int nMinorCol = 0;

	for (int i = 0; i < Dimension(); i++)
	{
		if (nRow == i)
			continue;
		nMinorCol = 0;

		for (int j = 0; j < Dimension(); j++)
		{
			if (nCol == j)
				continue;
			matMinor[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}


	return matMinor.Determinant();
}
