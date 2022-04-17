//
#pragma once
#ifndef VECTOR3D_H_
#define VECTOR3D_H_

//
typedef union Vector3D
{
	// some warning about a nameless struct
	// but it's way more convenient this way :(
	struct
	{ float x, y, z; };

	float m[3]{};

	/* Constructors */

	//
	Vector3D() = default;

	//
	Vector3D(float x, float y, float z);

	/* Assignment Operators */

	//
	Vector3D& operator=(const Vector3D& rhs);

	//
	Vector3D& operator+=(const Vector3D& rhs);

	//
	Vector3D& operator-=(const Vector3D& rhs);

	//
	Vector3D& operator*=(float rhs);

	//
	Vector3D& operator/=(float rhs);

	/* Unary Operators */

	//
	Vector3D operator-() const;

	/* Comparison Operators */

	//
	bool operator==(const Vector3D& rhs) const;

	/* Others */

	//
	float Length() const;

	//
	float LengthSq() const;

	//
	void Swap(Vector3D& rhs);

} Vector3D, Vec3, Point3D, Pt3;

//
Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);

//
Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs);

//
Vector3D operator*(const Vector3D& lhs, float rhs);

//
Vector3D operator*(float lhs, const Vector3D& rhs);

//
Vector3D operator/(const Vector3D& lhs, float rhs);

//
Vector3D Vector3DNormalize(const Vector3D& vec);

//
float Vector3DDistance(const Vector3D& v1, const Vector3D& v2);

//
float Vector3DSquaredDistance(const Vector3D& v1, const Vector3D& v2);

//
float Vector3DDotProduct(const Vector3D& v1, const Vector3D& v2);

//
float Vector3DCrossProductMag(const Vector3D& v1, const Vector3D& v2);

//
Vector3D Vector3DCrossProduct(const Vector3D& v1, const Vector3D& v2);

//
float Vector3DProjLength(const Vector3D& base, const Vector3D& vec);

//
Vector3D Vector3DProj(const Vector3D& base, const Vector3D& vec);

//
Vector3D Vector3DPerpProj(const Vector3D& base, const Vector3D& vec);

#endif // VECTOR3D_H_
