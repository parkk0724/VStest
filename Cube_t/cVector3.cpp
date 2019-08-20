#include "stdafx.h"
#include "cVector3.h"
#include <math.h>

#define EPSILON 0.0001f

cVector3::cVector3()
{
}


cVector3::~cVector3()
{
}

cVector3::cVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}

bool cVector3::operator==(cVector3 & vec)
{
	if (x - EPSILON <= vec.x && vec.x <= x + EPSILON &&
		y - EPSILON <= vec.y && vec.y <= y + EPSILON &&
		z - EPSILON <= vec.z && vec.z <= z + EPSILON)
	{
		return true;
	}
	return false;
}

bool cVector3::operator!=(cVector3 & vec)
{
	return !(*this == vec);
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

// >> : 내적 -> 결과값 스칼라
float cVector3::Dot(cVector3 & v1, cVector3 & v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

// >> : 외적 -> 두 벡터에 수직한 벡터
cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)
{
	float px = v1.y*v2.z - v1.z*v2.y;
	float py = v1.z*v2.x - v1.x*v2.z;
	float pz = v1.x*v2.y - v1.y*v2.x;
	return cVector3(px, py, pz);
}

// >> : 길이
float cVector3::Length()
{
	return (float)sqrt(x*x + y*y + z*z);
}

// >> : 단위 벡터
cVector3 cVector3::Normalize()
{
	float l = Length();

	float px = x / l;
	float py = y / l;
	float pz = z / l;

	return cVector3(px, py, pz);
}

cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix & mat)
{
	cVector3 vRet;
	vRet.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0] + 1.0f * mat[3][0];
	vRet.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1] + 1.0f * mat[3][1];
	vRet.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2] + 1.0f * mat[3][2];
	float w = v.x * mat[0][3] + v.y * mat[1][3] + v.z * mat[2][3] + 1.0f * mat[3][3];

	if (-EPSILON > w || w > EPSILON)
	{
		vRet.x /= w;
		vRet.y /= w;
		vRet.z /= w;
		//w /= w => 1
	}

	return vRet;
}

cVector3 cVector3::TransformNormal(cVector3 & v, cMatrix & mat)
{
	cVector3 vRet;
	vRet.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0];
	vRet.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1];
	vRet.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2];

	return vRet;
}
