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
		float a00, a01, a02;
		float a10, a11, a12;
		float a20, a21, a22;
	};

	float m[9]{};
	float m2[3][3];

	/* Constructors */

	//
	Matrix3x3() = default;

	//
	explicit Matrix3x3(const float* pArr_);

	//
	Matrix3x3(float a00_, float a01_, float a02_,
		float a10_, float a11_, float a12_,
		float a20_, float a21_, float a22_);

	/* Assignment operators */

	//
	Matrix3x3& operator=(const Matrix3x3& rhs_);

	//
	Matrix3x3& operator+=(const Matrix3x3& rhs_);

	//
	Matrix3x3& operator-=(const Matrix3x3& rhs_);

	//
	Matrix3x3& operator*=(const Matrix3x3& rhs_);

	/* Others */

	//
	float Determinant() const;

	//
	void Swap(Matrix3x3& rhs_);

} Matrix3x3, Mtx33;

//
Matrix3x3 operator+(const Matrix3x3& lhs_, const Matrix3x3& rhs_);

//
Matrix3x3 operator-(const Matrix3x3& lhs_, const Matrix3x3& rhs_);

//
Matrix3x3 operator*(const Matrix3x3& lhs_, const Matrix3x3& rhs_);

//
Vector2D operator*(const Matrix3x3& pMtx_, const Vector2D& rhs_);

//
Matrix3x3 Mtx33Identity();

//
Matrix3x3 Mtx33Translate(float x_, float y_);

//
Matrix3x3 Mtx33Scale(float x_, float y_);

//
Matrix3x3 Mtx33RotRad(float radians_);

//
Matrix3x3 Mtx33RotDeg(float degrees_);

//
Matrix3x3 Mtx33Shear(const Vector2D& shear_);

//
Matrix3x3 Mtx33Proj(const Vector2D& axis_);

//
Matrix3x3 Mtx33Transpose(const Matrix3x3& mtx_);

//
Matrix3x3 Mtx33Inverse(Matrix3x3* result_, float* determinant_, const Matrix3x3& mtx_);

#endif // MATRIX3X3_H_