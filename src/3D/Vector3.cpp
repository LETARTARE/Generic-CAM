#include "Vector3.h"

Vector3::~Vector3(void)
{
}

float Vector3::Abs(void)
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::Zero(void)
{
	x = y = z = 0.0;
}

Vector3 Vector3::Normalize(void)
{
	float d = Abs();
	if(d > 0){
		x /= d;
		y /= d;
		z /= d;
	}
	return Vector3(x, y, z);
}
