#pragma once

class cVector3;
class cMatrix
{
public:
	cMatrix();
	~cMatrix();
private:
	class cRow
	{
	private:
		std::vector<float> m_vecData;
	public:
		cRow();
		cRow(int nDimension);
		~cRow() {}
		void Resize(int nDimension);
		float & operator[] (int nIndex);
	};

	std::vector<cRow> m_vecData;


public:
	cMatrix(int nDimension);

	void Print();
	void Resize(int nDimension);
	int Dimension();

	static cMatrix Identity(int nDimension);
	cMatrix::cRow & operator[](int nIndex);
	bool operator == (cMatrix& mat);
	bool operator != (cMatrix& mat);
	cMatrix operator+(cMatrix& mat);
	cMatrix operator-(cMatrix& mat);
	cMatrix operator*(cMatrix& mat);
	cMatrix operator*(float f);

	cMatrix Inverse(OUT float& fDeterminat);
	float Determinant();
	cMatrix Adjoint();
	cMatrix Transpose();
	float Cofactor(int nRow, int nCol);
	float Minor(int nRow, int nCol);

	static cMatrix Scale(float x, float y, float z);
	static cMatrix Rotate(float x, float y, float z);

	static cMatrix Translation(float x, float y, float z);
	static cMatrix Translation(cVector3 & v);
	static cMatrix RotationX(float fAngle);
	static cMatrix RotationY(float fAngle);
	static cMatrix RotationZ(float fAngle);
	static cMatrix View(cVector3& vEye, cVector3& vLookAt, cVector3& vUp);
	static cMatrix Projection(float fFovY, float fAspect, float fNearZ, float fFarZ);
	static cMatrix Viewport(float x, float y, float w, float h, float minz, float maxz);

};



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