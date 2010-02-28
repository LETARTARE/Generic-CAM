#ifndef _CVECTOR3_H_
#define _CVECTOR3_H_

#include <cmath>

class Vector3 {
public:
	Vector3(float px = 0, float py = 0, float pz = 0) :
		x(px), y(py), z(pz)
	{
	}
	;
	~Vector3(void);
public:
	float x;
	float y;
	float z;

	float Abs();

	//	void operator=(const Vector3& a){x=a.x;y=a.y;z=a.z;};

	Vector3 operator+(const Vector3& a)
	{
		return Vector3(x + a.x, y + a.y, z + a.z);
	}
	Vector3 operator+=(const Vector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return Vector3(x, y, z);
	}

	Vector3 operator-(const Vector3& a)
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}
	Vector3 operator-=(const Vector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return Vector3(x, y, z);
	}

	Vector3 operator-()
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 operator*(const Vector3& b)
	{
		return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
	Vector3 operator*(const float &b)
	{
		return Vector3(x * b, y * b, z * b);
	}
	Vector3 operator/(const float &b)
	{
		return Vector3(x / b, y / b, z / b);
	}
	Vector3 operator/=(const float &b)
	{
		x /= b;
		y /= b;
		z /= b;
		return Vector3(x, y, z);
	}

	void Zero(void);
	void Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3 Normalize(void);
};

#endif // _CVECTOR3_H_
