//
#include "Matrix3x3.hpp"
#include <algorithm> // std::swap()
#include <corecrt_math_defines.h> // M_PI

constexpr float EPSILON = 0.0001f;
static const size_t sz = 3; // # of dimensions of matrix

//
Matrix3x3::Matrix3x3(const float* pArr)
{
	for (size_t i{ 0 }; i < sz * sz; ++i)
	{ m[i] = *(pArr + i); }
}

//
Matrix3x3::Matrix3x3(const float _00, const float _01, const float _02,
	const float _10, const float _11, const float _12,
	const float _20, const float _21, const float _22)
{
	m00 = _00; m01 = _01; m02 = _02;
	m10 = _10; m11 = _11; m12 = _12;
	m20 = _20; m21 = _21; m22 = _22;
}

//
Matrix3x3& Matrix3x3::operator=(const Matrix3x3& rhs)
{
	// copy swap idiom
	Matrix3x3 temp{ rhs };
	Swap(temp);
	return *this;
}

//
Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& rhs)
{ return *this = *this + rhs; }

//
Matrix3x3& Matrix3x3::operator-=(const Matrix3x3 & rhs)
{ return *this = *this - rhs; }

//
Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& rhs)
{ return *this = *this * rhs; }

//
float Matrix3x3::Determinant() const
{
	float result{ 0.0f };
	for (size_t i = 0; i < sz; ++i)
	{
		// this took a while...
		float det_2x2 = m[1 * sz + (i + 1) % sz] *		// a of 2x2
			m[2 * sz + (i + 2) % sz] - // d of 2x2
			m[1 * sz + (i + 2) % sz] *		// b of 2x2
			m[2 * sz + (i + 1) % sz];	// c of 2x2
		result += m[i] * det_2x2;
		// ends up being correct because the minus signs are accounted for
	}
	return  result;
}

//
void Matrix3x3::Swap(Matrix3x3& rhs)
{ std::swap((*this).m, rhs.m); }

//
Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
	Matrix3x3 result{ lhs };
	for (size_t i{0}; i < sz *sz; ++i)
	{ result.m[i] += rhs.m[i]; }
	return result;
}

//
Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
	Matrix3x3 result{ lhs };
	for (size_t i{ 0 }; i < sz * sz; ++i)
	{ result.m[i] -= rhs.m[i]; }
	return result;
}

//
Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
	float zeros[sz * sz] = { 0 };
	Matrix3x3 result(zeros);

	for (size_t i = 0; i < sz * sz; ++i)
	{
		for (size_t j = 0; j < sz; ++j)
		{ result.m[i] += lhs.m[(i / sz) * sz + j] * rhs.m[j * sz + i % sz]; }
	}
	return result;
}

//
Vector2D operator*(const Matrix3x3& pMtx, const Vector2D& rhs)
{
	const size_t n = 2; // # of dimensions of vector
	Vector2D result(0, 0);

	// applying effect of upper-left 2x2 submatrix of pMtx
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{ result.m[i] += pMtx.m[i * sz + j] * rhs.m[j]; }
	}

	// translation
	for (size_t i = 0; i < n; ++i)
	{ result.m[i] += pMtx.m[i * sz + (sz - 1)]; }
	return result;
}

//
Matrix3x3 Mtx33Identity(Matrix3x3& result)
{
	for (size_t i = 0; i < sz; ++i)
	{
		for (size_t j = 0; j < sz; ++j)
		{ result.m[i * sz + j] = (i == j) ? 1.0f : 0.0f; }
	}
	return result;
}

//
Matrix3x3 Mtx33Translate(Matrix3x3& result, const float x, const float y)
{
	Mtx33Identity(result);
	result.m02 = x;
	result.m12 = y;
	return result;
}

//
Matrix3x3 Mtx33Scale(Matrix3x3& result, const float x, const float y)
{
	Mtx33Identity(result);
	result.m00 = x;
	result.m11 = y;
	return result;
}

//
Matrix3x3 Mtx33RotRad(Matrix3x3& result, const float radians)
{
	Mtx33Identity(result);
	result.m00 = result.m11 = cosf(radians);
	result.m10 = sinf(radians);
	result.m01 = -result.m10;
	return result;
}

//
Matrix3x3 Mtx33RotDeg(Matrix3x3& result, const float degrees)
{ return Mtx33RotRad(result, static_cast<float>(degrees / 180.0f * M_PI)); }

//
Matrix3x3 Mtx33Transpose(Matrix3x3& result, const Matrix3x3& mtx)
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
Matrix3x3 Mtx33Inverse(Matrix3x3* result, float* determinant, const Matrix3x3& mtx)
{
	*determinant = mtx.Determinant();

	if (-EPSILON <= *determinant && *determinant <= EPSILON)
	{
		result = nullptr;
		throw("Determinant = 0 in Mtx33Inverse()");
	}

	Mtx33 adjoint, adjointTranspose;
	for (size_t i = 0; i < sz; ++i)
	{
		for (size_t j = 0; j < sz; ++j)
		{
			// this took a while...
			float det_2x2 = mtx.m[(i + 1) % sz * sz + (j + 1) % sz] *	   // a of 2x2
				mtx.m[(i + 2) % sz * sz + (j + 2) % sz] - // d of 2x2
				mtx.m[(i + 1) % sz * sz + (j + 2) % sz] *	   // b of 2x2
				mtx.m[(i + 2) % sz * sz + (j + 1) % sz];  // c of 2x2
			adjoint.m[i * sz + j] = det_2x2;
		}
	}

	Mtx33Transpose(adjointTranspose, adjoint);

	for (size_t i = 0; i < sz * sz; ++i)
	{ result->m[i] = adjointTranspose.m[i] / *determinant; }
	return *result;
}
