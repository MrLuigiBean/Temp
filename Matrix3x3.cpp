//
#include "Matrix3x3.hpp"
#include <algorithm> // std::swap()
#include <corecrt_math_defines.h> // M_PI

constexpr float EPSILON = 0.0001f;
static const size_t _sz = 3; // # of dimensions of matrix

const Vector2D e1_2D{ 1, 0 };
const Vector2D e2_2D{ 0, 1 };

//
Matrix3x3::Matrix3x3(const float* pArr_)
{
	for (size_t i{ 0 }; i < _sz * _sz; ++i)
	{ m[i] = *(pArr_ + i); }
}

//
Matrix3x3::Matrix3x3(const float a00_, const float a01_, const float a02_,
	const float a10_, const float a11_, const float a12_,
	const float a20_, const float a21_, const float a22_)
{
	a00 = a00_; a01 = a01_; a02 = a02_;
	a10 = a10_; a11 = a11_; a12 = a12_;
	a20 = a20_; a21 = a21_; a22 = a22_;
}

//
Matrix3x3& Matrix3x3::operator=(const Matrix3x3& rhs_)
{
	// copy swap idiom
	Matrix3x3 temp{ rhs_ };
	Swap(temp);
	return *this;
}

//
Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& rhs_)
{ return *this = *this + rhs_; }

//
Matrix3x3& Matrix3x3::operator-=(const Matrix3x3 & rhs_)
{ return *this = *this - rhs_; }

//
Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& rhs_)
{ return *this = *this * rhs_; }

//
float Matrix3x3::Determinant() const
{
	float result{ 0.0f };
	for (size_t i = 0; i < _sz; ++i)
	{
		// this took a while...
		float det_2x2 = m[1 * _sz + (i + 1) % _sz] *		// a of 2x2
			m[2 * _sz + (i + 2) % _sz] - // d of 2x2
			m[1 * _sz + (i + 2) % _sz] *		// b of 2x2
			m[2 * _sz + (i + 1) % _sz];	// c of 2x2
		result += m[i] * det_2x2;
		// ends up being correct because the minus signs are accounted for
	}
	return  result;
}

//
void Matrix3x3::Swap(Matrix3x3& rhs_)
{ std::swap((*this).m, rhs_.m); }

//
Matrix3x3 operator+(const Matrix3x3& lhs_, const Matrix3x3& rhs_)
{
	Matrix3x3 result{ lhs_ };
	for (size_t i{0}; i < _sz *_sz; ++i)
	{ result.m[i] += rhs_.m[i]; }
	return result;
}

//
Matrix3x3 operator-(const Matrix3x3& lhs_, const Matrix3x3& rhs_)
{
	Matrix3x3 result{ lhs_ };
	for (size_t i{ 0 }; i < _sz * _sz; ++i)
	{ result.m[i] -= rhs_.m[i]; }
	return result;
}

//
Matrix3x3 operator*(const Matrix3x3& lhs_, const Matrix3x3& rhs_)
{
	float zeros[_sz * _sz] = { 0 };
	Matrix3x3 result(zeros);

	for (size_t i = 0; i < _sz * _sz; ++i)
	{
		for (size_t j = 0; j < _sz; ++j)
		{ result.m[i] += lhs_.m[(i / _sz) * _sz + j] * rhs_.m[j * _sz + i % _sz]; }
	}
	return result;
}

//
Vector2D operator*(const Matrix3x3& pMtx_, const Vector2D& rhs_)
{
	const size_t n = 2; // # of dimensions of vector
	Vector2D result(0, 0);

	// applying effect of upper-left 2x2 submatrix of pMtx_
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{ result.m[i] += pMtx_.m[i * _sz + j] * rhs_.m[j]; }
	}

	// translation
	for (size_t i = 0; i < n; ++i)
	{ result.m[i] += pMtx_.m[i * _sz + (_sz - 1)]; }
	return result;
}

//
Matrix3x3 Mtx33Identity()
{
	Matrix3x3 result;
	for (size_t i = 0; i < _sz; ++i)
	{
		for (size_t j = 0; j < _sz; ++j)
		{ result.m[i * _sz + j] = (i == j) ? 1.0f : 0.0f; }
	}
	return result;
}

//
Matrix3x3 Mtx33Translate(const float x_, const float y_)
{
	Matrix3x3 result = Mtx33Identity();
	result.a02 = x_;
	result.a12 = y_;
	return result;
}

//
Matrix3x3 Mtx33Scale(const float x_, const float y_)
{
	Matrix3x3 result = Mtx33Identity();
	result.a00 = x_;
	result.a11 = y_;
	return result;
}

//
Matrix3x3 Mtx33RotRad(const float radians_)
{
	Matrix3x3 result = Mtx33Identity();
	result.a00 = result.a11 = cosf(radians_);
	result.a10 = sinf(radians_);
	result.a01 = -result.a10;
	return result;
}

//
Matrix3x3 Mtx33RotDeg(const float degrees_)
{ return Mtx33RotRad(static_cast<float>(degrees_ / 180.0f * M_PI)); }

//
Matrix3x3 Mtx33Shear(const Vector2D& shear_)
{
	Vector2D normalised_shear{ Vector2DNormalize(shear_) };
	normalised_shear = { -normalised_shear.y, normalised_shear.x };
	// v' = v + (n dot v)s
	const Vector2D e1_prime = e1_2D + Vector2DDotProduct(normalised_shear, e1_2D) * shear_;
	const Vector2D e2_prime = e2_2D + Vector2DDotProduct(normalised_shear, e2_2D) * shear_;
	Matrix3x3 result = Mtx33Identity();
	for (size_t i{ 0 }; i < _sz - 1; ++i)
	{
		result.m2[i][0] = e1_prime.m[i];
		result.m2[i][1] = e2_prime.m[i];
	}
	return result;
}

//
Matrix3x3 Mtx33Proj(const Vector2D& axis_)
{
	// v' = proj(axis_)v
	const Vector2D e1_prime = Vector2DProj(axis_, e1_2D);
	const Vector2D e2_prime = Vector2DProj(axis_, e2_2D);
	Matrix3x3 result = Mtx33Identity();
	for (size_t i{0}; i < _sz - 1; ++i)
	{
		result.m2[i][0] = e1_prime.m[i];
		result.m2[i][1] = e2_prime.m[i];
	}
	return result;
}

//
Matrix3x3 Mtx33Transpose(const Matrix3x3& mtx_)
{
	Matrix3x3 result;
	for (size_t i = 0; i < _sz; ++i)
	{
		for (size_t j = 0; j < _sz; ++j)
		{ result.m[i * _sz + j] = mtx_.m[j * _sz + i]; }
		// swapped the i and j for mtx
	}
	return result;
}

//
Matrix3x3 Mtx33Inverse(Matrix3x3* result_, float* determinant_, const Matrix3x3& mtx_)
{
	*determinant_ = mtx_.Determinant();

	if (-EPSILON <= *determinant_ && *determinant_ <= EPSILON)
	{
		result_ = nullptr;
		throw "Determinant = 0 in Mtx33Inverse()";
	}

	Mtx33 adjoint, adjoint_transpose;
	for (size_t i = 0; i < _sz; ++i)
	{
		for (size_t j = 0; j < _sz; ++j)
		{
			// this took a while...
			float det_2x2 = mtx_.m[(i + 1) % _sz * _sz + (j + 1) % _sz] *	   // a of 2x2
				mtx_.m[(i + 2) % _sz * _sz + (j + 2) % _sz] - // d of 2x2
				mtx_.m[(i + 1) % _sz * _sz + (j + 2) % _sz] *	   // b of 2x2
				mtx_.m[(i + 2) % _sz * _sz + (j + 1) % _sz];  // c of 2x2
			adjoint.m[i * _sz + j] = det_2x2;
		}
	}

	adjoint_transpose = Mtx33Transpose(adjoint);

	for (size_t i = 0; i < _sz * _sz; ++i)
	{ result_->m[i] = adjoint_transpose.m[i] / *determinant_; }
	return *result_;
}
