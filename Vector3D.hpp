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
	Vector3D(float x_, float y_, float z_);

	/* Assignment Operators */

	//
	Vector3D& operator=(const Vector3D& rhs_);

	//
	Vector3D& operator+=(const Vector3D& rhs_);

	//
	Vector3D& operator-=(const Vector3D& rhs_);

	//
	Vector3D& operator*=(float rhs_);

	//
	Vector3D& operator/=(float rhs_);

	/* Unary Operators */

	//
	Vector3D operator-() const;

	/* Comparison Operators */

	//
	bool operator==(const Vector3D& rhs_) const;

	/* Others */

	//
	float Length() const;

	//
	float LengthSq() const;

	//
	void Swap(Vector3D& rhs_);

} Vector3D, Vec3, Point3D, Pt3;

//
Vector3D operator+(const Vector3D& lhs_, const Vector3D& rhs_);

//
Vector3D operator-(const Vector3D& lhs_, const Vector3D& rhs_);

//
Vector3D operator*(const Vector3D& lhs_, float rhs_);

//
Vector3D operator*(float lhs_, const Vector3D& rhs_);

//
Vector3D operator/(const Vector3D& lhs_, float rhs_);

//
Vector3D Vector3DNormalize(const Vector3D& vec_);

//
float Vector3DDistance(const Vector3D& vec_0_, const Vector3D& vec_1_);

//
float Vector3DSquaredDistance(const Vector3D& vec_0_, const Vector3D& vec_1_);

//
float Vector3DDotProduct(const Vector3D& vec_0_, const Vector3D& vec_1_);

//
float Vector3DCrossProductMag(const Vector3D& vec_0_, const Vector3D& vec_1_);

//
Vector3D Vector3DCrossProduct(const Vector3D& vec_0_, const Vector3D& vec_1_);

//
float Vector3DProjLength(const Vector3D& base_, const Vector3D& vec_);

//
Vector3D Vector3DProj(const Vector3D& base_, const Vector3D& vec_);

//
Vector3D Vector3DPerpProj(const Vector3D& base_, const Vector3D& vec_);

#endif // VECTOR3D_H_
