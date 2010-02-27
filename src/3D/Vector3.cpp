#include "Vector3.h"

CVector3::~CVector3(void)
{
}

float CVector3::Abs(void)
{
	return sqrt(x * x + y * y + z * z);
}

void CVector3::Zero(void)
{
	x = y = z = 0.0;
}

CVector3 CVector3::Normalize(void)
{
	float d = Abs();
	if(d > 0){
		x /= d;
		y /= d;
		z /= d;
	}
	return CVector3(x, y, z);
}
