#ifndef _CVECTOR3_H_
#define _CVECTOR3_H_

#include <cmath>

class CVector3 {
public:
	CVector3(float px = 0, float py = 0, float pz = 0) :
		x(px), y(py), z(pz)
	{
	}
	;
	~CVector3(void);
public:
	float x;
	float y;
	float z;

	float Abs();

	//	void operator=(const CVector3& a){x=a.x;y=a.y;z=a.z;};

	CVector3 operator+(const CVector3& a)
	{
		return CVector3(x + a.x, y + a.y, z + a.z);
	}
	CVector3 operator+=(const CVector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return CVector3(x, y, z);
	}

	CVector3 operator-(const CVector3& a)
	{
		return CVector3(x - a.x, y - a.y, z - a.z);
	}
	CVector3 operator-=(const CVector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return CVector3(x, y, z);
	}

	CVector3 operator-()
	{
		return CVector3(-x, -y, -z);
	}

	CVector3 operator*(const CVector3& b)
	{
		return CVector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
	CVector3 operator*(const float &b)
	{
		return CVector3(x * b, y * b, z * b);
	}
	CVector3 operator/(const float &b)
	{
		return CVector3(x / b, y / b, z / b);
	}
	CVector3 operator/=(const float &b)
	{
		x /= b;
		y /= b;
		z /= b;
		return CVector3(x, y, z);
	}

	void Zero(void);
	void Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	CVector3 Normalize(void);
};

#endif // _CVECTOR3_H_
