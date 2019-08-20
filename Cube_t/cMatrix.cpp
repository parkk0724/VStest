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

cMatrix cMatrix::Scale(float x, float y, float z)
{
	cMatrix matRet(4);
	matRet = matRet.Identity(matRet.Dimension());
	matRet[0][0] = x;
	matRet[1][1] = y;
	matRet[2][2] = z;

	return matRet;
}

cMatrix cMatrix::Rotate(float x, float y, float z)
{
	return RotationX(x) * RotationY(y) * RotationZ(z);
}

cMatrix cMatrix::Translation(float x, float y, float z)
{
	cMatrix matRet = cMatrix::Identity(4);

	matRet[3][0] = x;
	matRet[3][1] = y;
	matRet[3][2] = z;

	return matRet;
}

cMatrix cMatrix::Translation(cVector3 & v)
{
	cMatrix matRet = matRet.Identity(matRet.Dimension());
	matRet[3][0] = v.x;
	matRet[3][1] = v.y;
	matRet[3][2] = v.z;
	return matRet;
}

cMatrix cMatrix::RotationX(float fAngle)
{
	cMatrix matRet(4);
	matRet = matRet.Identity(matRet.Dimension());
	matRet[1][1] = cos(fAngle);
	matRet[1][2] = sin(fAngle);
	matRet[2][1] = -sin(fAngle);
	matRet[2][2] = cos(fAngle);
	return matRet;
}

cMatrix cMatrix::RotationY(float fAngle)
{
	cMatrix matRet(4);
	matRet = matRet.Identity(matRet.Dimension());
	matRet[0][0] = cos(fAngle);
	matRet[0][2] = -sin(fAngle);
	matRet[2][0] = sin(fAngle);
	matRet[2][2] = cos(fAngle);
	return matRet;
}

cMatrix cMatrix::RotationZ(float fAngle)
{
	cMatrix matRet(4);
	matRet = matRet.Identity(matRet.Dimension());
	matRet[0][0] = cos(fAngle);
	matRet[0][1] = sin(fAngle);
	matRet[1][0] = -sin(fAngle);
	matRet[1][1] = cos(fAngle);
	return matRet;
}

cMatrix cMatrix::View(cVector3 & vEye, cVector3 & vLookAt, cVector3 & vUp)
{
	cVector3 l = (vLookAt - vEye).Normalize();
	cVector3 r = cVector3::Cross(vUp, l).Normalize();
	cVector3 u = cVector3::Cross(l, r).Normalize();

	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = r.x; matRet[0][1] = u.x; matRet[0][2] = l.x;
	matRet[1][0] = r.y; matRet[1][1] = u.y; matRet[1][2] = l.y;
	matRet[2][0] = r.z; matRet[2][1] = u.z; matRet[2][2] = l.z;

	matRet[3][0] = -cVector3::Dot(r, vEye);
	matRet[3][1] = -cVector3::Dot(u, vEye);
	matRet[3][2] = -cVector3::Dot(l, vEye);

	return matRet;
}

cMatrix cMatrix::Projection(float fFovY, float fAspect, float fNearZ, float fFarZ)
{
	cMatrix matRet = cMatrix::Identity(4);
	float fScaleY = 1.0f / tanf(fFovY / 2.0f);
	float fScaleX = fScaleY / fAspect;

	matRet[0][0] = fScaleX;
	matRet[1][1] = fScaleY;
	matRet[2][2] = fFarZ / (fFarZ - fNearZ);
	matRet[2][3] = 1.0f;
	matRet[3][2] = -fFarZ * fNearZ / (fFarZ - fNearZ);
	matRet[3][3] = 0.0f;

	return matRet;
}

cMatrix cMatrix::Viewport(float x, float y, float w, float h, float minz, float maxz)
{
	cMatrix matRet = cMatrix::Identity(4);

	matRet[0][0] = w / 2.0f;
	matRet[1][1] = -h / 2.0f;
	matRet[2][2] = maxz - minz;
	matRet[3][0] = x + w / 2.0f;
	matRet[3][1] = y + h / 2.0f;
	matRet[3][2] = minz;

	return matRet;
}


/*
View Matrix

l = look vector
r = right vector
u = up vector

r.x			u.x			l.x			0
r.y			u.y			l.y			0
r.z			u.z			l.z			0
-r dot eye	-u dot eye	-l dot eye	1

Projection Matrix
sy = cot(fovy/2.0f)  => 1.0f / tanf(fFovY, 2.0f);
sx = sy/ aspect

sx				0				0					0
0				sy				0					0
0				0				fz/(fz-nz)			1
0				0				-fz*nz/(fz-nz)		0

Fov : PI/4.0f , PI = 180 Field of View
Aspect : width / height
farZ : 1000.0f
nearZ : 1.0f


Viewport Matrix
w/2.0f			0			0			0
0				-h/2.0f		0			0
0				0			maxz-minz	0
x+w/2.0f		y+h/2.0f	minz		1

maxz = 1
minz = 0

S(scale) R(Rotation) T(Translate)
SRT => World Matrix
WVP => World * View * Proj

ViewPort -> 최종 좌표로 그려주면 끝

*/