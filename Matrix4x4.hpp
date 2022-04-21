//
#pragma once
#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include "Vector3D.hpp"

extern const Vector3D e1_3D; // {1, 0, 0}
extern const Vector3D e2_3D; // {0, 1, 0}
extern const Vector3D e3_3D; // {0, 0, 1}

//
typedef union Matrix4x4
{
	// some warning about a nameless struct
	// but it's way more convenient this way :(
	struct
	{
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};

	float m[16]{};
	float m2[4][4];

	/* Constructors */

	//
	Matrix4x4() = default; // all values initialized to 0.0f

	//
	explicit Matrix4x4(const float* pArr);

	//
	Matrix4x4(float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33);

	/* Assignment operators */

	//
	Matrix4x4& operator=(const Matrix4x4& rhs);

	//
	Matrix4x4& operator+=(const Matrix4x4& rhs);

	//
	Matrix4x4& operator-=(const Matrix4x4& rhs);

	//
	Matrix4x4& operator*=(const Matrix4x4& rhs);

	/* Others */

	//
	float Determinant() const;

	//
	void Swap(Matrix4x4& rhs);

}Matrix4x4, Mtx44;

//
Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs);

//
Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs);

//
Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);

//
Vector3D operator*(const Matrix4x4& mtx, const Vector3D& rhs);

//
Matrix4x4 Mtx44Identity(Matrix4x4& result);

//
Matrix4x4 Mtx44Translate(Matrix4x4& result, float x, float y, float z);

//
Matrix4x4 Mtx44Scale(Matrix4x4& result, float x, float y, float z);

//
Matrix4x4 Mtx44RotRad(Matrix4x4& result, Vector3D axis, float radians);

//
Matrix4x4 Mtx44RotDeg(Matrix4x4& result, Vector3D axis, float degrees);

//
Matrix4x4 Mtx44Transpose(Matrix4x4& result, const Matrix4x4& mtx);

//
//inverse

#endif // MATRIX4X4_H_
