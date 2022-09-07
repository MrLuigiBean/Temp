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
		float a00, a01, a02, a03;
		float a10, a11, a12, a13;
		float a20, a21, a22, a23;
		float a30, a31, a32, a33;
	};

	float m[16]{};
	float m2[4][4];

	/* Constructors */

	//
	Matrix4x4() = default; // all values initialized to 0.0f

	//
	explicit Matrix4x4(const float* pArr_);

	//
	Matrix4x4(float a00_, float a01_, float a02_, float a03_,
		float a10_, float a11_, float a12_, float a13_,
		float a20_, float a21_, float a22_, float a23_,
		float a30_, float a31_, float a32_, float a33_);

	/* Assignment operators */

	//
	Matrix4x4& operator=(const Matrix4x4& rhs_);

	//
	Matrix4x4& operator+=(const Matrix4x4& rhs_);

	//
	Matrix4x4& operator-=(const Matrix4x4& rhs_);

	//
	Matrix4x4& operator*=(const Matrix4x4& rhs_);

	/* Others */

	//
	float Determinant() const;

	//
	void Swap(Matrix4x4& rhs_);

}Matrix4x4, Mtx44;

//
Matrix4x4 operator+(const Matrix4x4& lhs_, const Matrix4x4& rhs_);

//
Matrix4x4 operator-(const Matrix4x4& lhs_, const Matrix4x4& rhs_);

//
Matrix4x4 operator*(const Matrix4x4& lhs_, const Matrix4x4& rhs_);

//
Vector3D operator*(const Matrix4x4& mtx_, const Vector3D& rhs_);

//
Matrix4x4 Mtx44Identity();

//
Matrix4x4 Mtx44Translate(float x_, float y_, float z_);

//
Matrix4x4 Mtx44Scale(float x_, float y_, float z_);

//
Matrix4x4 Mtx44RotRad(Vector3D axis_, float radians_);

//
Matrix4x4 Mtx44RotDeg(Vector3D axis_, float degrees_);

//
Matrix4x4 Mtx44Shear(const Vector3D& shear_, const Vector3D& normal_);

//
Matrix4x4 Mtx44Proj(const Vector3D& normal_);

//
Matrix4x4 Mtx44Transpose(const Matrix4x4& mtx_);

//
Matrix4x4 Mtx44Inverse(Matrix4x4* result_, float* determinant_, const Matrix4x4& mtx_);

#endif // MATRIX4X4_H_
