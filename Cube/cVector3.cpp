#include "stdafx.h"

cVector3::cVector3()
{
}


cVector3::~cVector3()
{
}

cVector3::cVector3(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

bool cVector3::operator==(cVector3 & vec)
{
	if (x == vec.x && y == vec.y && z == vec.z) return true;

	return false;
}

bool cVector3::operator!=(cVector3 & vec)
{
	if (x == vec.x && y == vec.y && z == vec.z) return false;

	return true;
}

cVector3 cVector3::operator+(cVector3 & vec)
{
	float px = x + vec.x;
	float py = y + vec.y;
	float pz = z + vec.z;

	return cVector3(px, py, pz);
}

cVector3 cVector3::operator-(cVector3 & vec)
{
	float px = x - vec.x;
	float py = y - vec.y;
	float pz = z - vec.z;

	return cVector3(px, py, pz);
}

cVector3 cVector3::operator*(cVector3 & vec)
{
	float px = x * vec.x;
	float py = y * vec.y;
	float pz = z * vec.z;

	return cVector3(px, py, pz);
}

cVector3 cVector3::operator*(float f)
{
	float px = x * f;
	float py = y * f;
	float pz = z * f;

	return cVector3(px, py, pz);
}

cVector3 cVector3::operator/(float f)
{
	float px = x / f;
	float py = y / f;
	float pz = z / f;

	return cVector3(px, py, pz);
}

float cVector3::Dot(cVector3 & v1, cVector3 & v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)
{
	float px = v1.y*v2.z - v1.z*v2.y;
	float py = v1.z*v2.x - v1.x*v2.z;
	float pz = v1.x*v2.y - v1.y*v2.x;
	return cVector3(px, py, pz);
}

float cVector3::Length()
{
	float result = sqrt(x*x + y*y + z*z);

	return result;
}

cVector3 cVector3::Normalize()
{
	float px = x / Length();
	float py = y / Length();
	float pz = z / Length();;

	return cVector3(px, py, pz);
}

cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix & mat)
{
	cVector3 pOut;

	pOut.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z* mat[2][0] + v.w * mat[3][0];
	pOut.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z* mat[2][1] + v.w * mat[3][1];
	pOut.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z* mat[2][2] + v.w * mat[3][2];
	pOut.w = v.x * mat[0][3] + v.y * mat[1][3] + v.z* mat[2][3] + v.w * mat[3][3];

	return pOut;
}

cVector3 cVector3::TransformNormal(cVector3 & v, cMatrix & mat)
{
	cVector3 pOut;
	if (mat.Dimension() == 4)
	{
		for (int i = 0; i < mat.Dimension() - 1; i++)
		{
			float result = 0.f;
			result += v.x * mat[i][0];
			result += v.y * mat[i][1];
			result += v.z * mat[i][2];
			result += 0 * mat[i][3];
			if (i == 0) pOut.x = result;
			else if (i == 1) pOut.y = result;
			else if (i == 2) pOut.z = result;
		}
	}
	return pOut;
}
