//
#include "Matrix4x4.hpp"
#include <algorithm> // std::swap()
#include <corecrt_math_defines.h> // M_PI

static const size_t sz = 4; // # of dimensions of matrix

const Vector3D e1{ 1, 0, 0 };
const Vector3D e2{ 0, 1, 0 };
const Vector3D e3{ 0, 0, 1 };

//
Matrix4x4::Matrix4x4(const float* pArr)
{
	for (size_t i{ 0 }; i < sz * sz; ++i)
	{ m[i] = *(pArr + i); }
}

//
Matrix4x4::Matrix4x4(const float _00, const float _01, const float _02, const float _03,
	const float _10, const float _11, const float _12, const float _13,
	const float _20, const float _21, const float _22, const float _23,
	const float _30, const float _31, const float _32, const float _33)
{
	m00 = _00; m01 = _01; m02 = _02; m03 = _03;
	m10 = _10; m11 = _11; m12 = _12; m13 = _13;
	m20 = _20; m21 = _21; m22 = _22; m23 = _23;
	m30 = _30; m31 = _31; m32 = _32; m33 = _33;
}

//
Matrix4x4& Matrix4x4::operator=(const Matrix4x4& rhs)
{
	// copy swap idiom
	Matrix4x4 temp{ rhs };
	Swap(temp);
	return *this;
}

//
Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
{ return *this = *this + rhs; }

//
Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs)
{ return *this = *this - rhs; }

//
Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs)
{ return *this = *this * rhs; }

//
void Matrix4x4::Swap(Matrix4x4& rhs)
{ std::swap((*this).m, rhs.m); }

//
Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result{ lhs };
	for (size_t i{ 0 }; i < sz * sz; ++i)
	{ result.m[i] += rhs.m[i]; }
	return result;
}

//
Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result{ lhs };
	for (size_t i{ 0 }; i < sz * sz; ++i)
	{ result.m[i] -= rhs.m[i]; }
	return result;
}

//
Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs) { return {}; }

//
Vector3D operator*(const Matrix4x4& pMtx, const Vector3D& rhs) { return {}; }

//
Matrix4x4& Mtx44Identity(Matrix4x4& result)
{
	for (size_t i = 0; i < sz; ++i)
	{
		for (size_t j = 0; j < sz; ++j)
		{ result.m[i * sz + j] = (i == j) ? 1.0f : 0.0f; }
	}
	return result;
}

//
Matrix4x4 Mtx44Translate(Matrix4x4& result, const float x, const float y, const float z)
{
	Mtx44Identity(result);
	result.m03 = x;
	result.m13 = y;
	result.m23 = z;
	return result;
}

//
Matrix4x4 Mtx44Scale(Matrix4x4& result, const float x, const float y, const float z)
{
	Mtx44Identity(result);
	result.m00 = x;
	result.m11 = y;
	result.m22 = z;
	return result;
}

//
Matrix4x4 Mtx44RotRad(Matrix4x4& result, const Vector3D axis, const float radians)
{
	// e1 rotation
	if (axis == -e1)
	{ return Mtx44RotRad(result, e1, -radians); }
	if (axis == e1)
	{
		Mtx44Identity(result);
		result.m11 = result.m22 = cosf(radians);
		result.m21 = sinf(radians);
		result.m12 = -result.m21;
		return result;
	}

	// e2 rotation
	if (axis == -e2)
	{ return Mtx44RotRad(result, e2, -radians); }
	if (axis == e2)
	{
		Mtx44Identity(result);
		result.m00 = result.m22 = cosf(radians);
		result.m02 = sinf(radians);
		result.m20 = -result.m02;
		return result;
	}

	// e3 rotation
	if (axis == -e3)
	{ return Mtx44RotRad(result, e3, -radians); }
	if (axis == e3)
	{
		Mtx44Identity(result);
		result.m00 = result.m11 = cosf(radians);
		result.m10 = sinf(radians);
		result.m01 = -result.m10;
		return result;
	}

	// general rotation
	;
	return result;
}

//
Matrix4x4 Mtx44RotDeg(Matrix4x4& result, const Vector3D axis, const float degrees)
{ return Mtx44RotRad(result, axis, static_cast<float>(degrees / 180.0f * M_PI)); }
//
Matrix4x4 Mtx44Transpose(Matrix4x4& result, const Matrix4x4& mtx)
{
	for (size_t i = 0; i < sz; ++i)
	{
		for (size_t j = 0; j < sz; ++j)
		{ result.m[i * sz + j] = mtx.m[j * sz + i]; }
		// swapped the i and j for mtx
	}
	return result;
}

//
//inverse
