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
	for (int i = 0; i < nDimension; i++)
	{
		float f = rand() % 10;
		m_vecData.push_back(f);
	}
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
	for (int i = 0; i < nDimension; i++)
	{
		cRow r(nDimension);
		m_vecData.push_back(r);
	}
}

void cMatrix::Print()
{
	for (int i = 0; i < m_vecData.size(); i++)
	{
		for (int j = 0; j < m_vecData.size(); j++)
		{
			cout << m_vecData[i][j] << "\t";
		}
		cout << endl;
	}
}

void cMatrix::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
}

int cMatrix::Dimension()
{
	return m_vecData.size();
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix m(nDimension);
	for(int i =0; i < nDimension; i++)
	{
		for (int j = 0; j < nDimension; j++)
		{
			if (i == j) m[i][j] = 1;
			else m[i][j] = 0;
		}
	}

	return m;
}

cMatrix::cRow & cMatrix::operator[](int nIndex)
{
	return m_vecData[nIndex];
	// TODO: 여기에 반환 구문을 삽입합니다.
}

bool cMatrix::operator==(cMatrix & mat)
{
	if (mat.Dimension() != Dimension()) return false;

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			if (mat[i][j] != m_vecData[i][j]) return false;
		}
	}
	return true;
}

bool cMatrix::operator!=(cMatrix & mat)
{
	if (mat.Dimension() != Dimension()) return true;

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			if (mat[i][j] != m_vecData[i][j]) return true;
		}
	}
	return false;
}

cMatrix cMatrix::operator+(cMatrix & mat)
{
	if (mat.Dimension() != Dimension()) return *this;

	cMatrix m(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			m[i][j] = m_vecData[i][j] + mat[i][j];
		}
	}

	return m;
}

cMatrix cMatrix::operator-(cMatrix & mat)
{
	if (mat.Dimension() != Dimension()) return *this;

	cMatrix m(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			m[i][j] = m_vecData[i][j] - mat[i][j];
		}
	}

	return m;
}

cMatrix cMatrix::operator*(cMatrix & mat)
{
	if (mat.Dimension() != Dimension()) return *this;

	cMatrix m(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			float f = 0;
			for (int k = 0; k < Dimension(); k++)
			{
				f += m_vecData[j][k] * mat[k][j];
			}
			m[j][i] = f;
		}
	}

	return m;
}

cMatrix cMatrix::operator*(float f)
{
	cMatrix m(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			m[i][j] = m_vecData[i][j] * f;
		}
	}

	return m;
}

cMatrix cMatrix::Inverse(OUT float & fDeterminat)
{
	return cMatrix();
}

float cMatrix::Determinant()
{
	for (int i = 0; i < Dimension(); i++)
	{
		Minor(0, i, *this);
	}
	return 0.0f;
}

cMatrix cMatrix::Adjoint()
{
	return cMatrix();
}

cMatrix cMatrix::Transpose()
{
	return cMatrix();
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	return 0.0f;
}

float cMatrix::Minor(int nRow, int nCol, cMatrix m)
{
	float f = 0;

	if (m.Dimension() == 2)
	{
		f = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
	else Minor(0, i, m);

	for (int i = 0; i < m.Dimension(); i++)
	{
		int r = 1;
		cMatrix temp(m.Dimension() - 1);

		for (int j = 0; j < temp.Dimension(); j++)
		{
			int c = 0;
			for (int k = 0; k < temp.Dimension(); k++)
			{
				if (c == i) c++;
				temp[j][k] = m[r][c];
			}
			r++;
		}
	}

	return f;
}
