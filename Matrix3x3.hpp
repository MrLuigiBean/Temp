//
#pragma once
#ifndef MATRIX3X3_H_
#define MATRIX3X3_H_

#include "Vector2D.hpp"

extern const Vector2D e1_2D; // {1, 0}
extern const Vector2D e2_2D; // {0, 1}

//
typedef union Matrix3x3
{
	// some warning about a nameless struct
	// but it's way more convenient this way :(
	struct
	{
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;
	};

	float m[9]{};
	float m2[3][3];

	/* Constructors */

	//
	Matrix3x3() = default;

	//
	explicit Matrix3x3(const float* pArr);

	//
	Matrix3x3(float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22);

	/* Assignment operators */

	//
	Matrix3x3& operator=(const Matrix3x3& rhs);

	//
	Matrix3x3& operator+=(const Matrix3x3& rhs);

	//
	Matrix3x3& operator-=(const Matrix3x3& rhs);

	//
	Matrix3x3& operator*=(const Matrix3x3& rhs);

	/* Others */

	//
	float Determinant() const;

	//
	void Swap(Matrix3x3& rhs);

} Matrix3x3, Mtx33;

//
Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs);

//
Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs);

//
Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);

//
Vector2D operator*(const Matrix3x3& pMtx, const Vector2D& rhs);

//
Matrix3x3 Mtx33Identity();

//
Matrix3x3 Mtx33Translate(float x, float y);

//
Matrix3x3 Mtx33Scale(float x, float y);

//
Matrix3x3 Mtx33RotRad(float radians);

//
Matrix3x3 Mtx33RotDeg(float degrees);

//
Matrix3x3 Mtx33Shear(const Vector2D& shear);

//
Matrix3x3 Mtx33Proj(const Vector2D& axis);

//
Matrix3x3 Mtx33Transpose(const Matrix3x3& mtx);

//
Matrix3x3 Mtx33Inverse(Matrix3x3* result, float* determinant, const Matrix3x3& mtx);

#endif // MATRIX3X3_H_