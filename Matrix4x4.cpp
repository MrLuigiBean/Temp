//
#include "Matrix4x4.hpp"
#include <algorithm> // std::swap()
#include <corecrt_math_defines.h> // M_PI

constexpr float EPSILON = 0.0001f;
static const size_t _sz = 4; // # of dimensions of matrix

const Vector3D e1_3D{ 1, 0, 0 };
const Vector3D e2_3D{ 0, 1, 0 };
const Vector3D e3_3D{ 0, 0, 1 };

//
Matrix4x4::Matrix4x4(const float* pArr_)
{
	for (size_t i{ 0 }; i < _sz * _sz; ++i)
	{ m[i] = *(pArr_ + i); }
}

//
Matrix4x4::Matrix4x4(const float a00_, const float a01_, const float a02_, const float a03_,
	const float a10_, const float a11_, const float a12_, const float a13_,
	const float a20_, const float a21_, const float a22_, const float a23_,
	const float a30_, const float a31_, const float a32_, const float a33_)
{
	a00 = a00_; a01 = a01_; a02 = a02_; a03 = a03_;
	a10 = a10_; a11 = a11_; a12 = a12_; a13 = a13_;
	a20 = a20_; a21 = a21_; a22 = a22_; a23 = a23_;
	a30 = a30_; a31 = a31_; a32 = a32_; a33 = a33_;
}

//
Matrix4x4& Matrix4x4::operator=(const Matrix4x4& rhs_)
{
	// copy swap idiom
	Matrix4x4 temp{ rhs_ };
	Swap(temp);
	return *this;
}

//
Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs_)
{ return *this = *this + rhs_; }

//
Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs_)
{ return *this = *this - rhs_; }

//
Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs_)
{ return *this = *this * rhs_; }

//
float Matrix4x4::Determinant() const
{
	return 0;
}

//
void Matrix4x4::Swap(Matrix4x4& rhs_)
{ std::swap((*this).m, rhs_.m); }

//
Matrix4x4 operator+(const Matrix4x4& lhs_, const Matrix4x4& rhs_)
{
	Matrix4x4 result{ lhs_ };
	for (size_t i{ 0 }; i < _sz * _sz; ++i)
	{ result.m[i] += rhs_.m[i]; }
	return result;
}

//
Matrix4x4 operator-(const Matrix4x4& lhs_, const Matrix4x4& rhs_)
{
	Matrix4x4 result{ lhs_ };
	for (size_t i{ 0 }; i < _sz * _sz; ++i)
	{ result.m[i] -= rhs_.m[i]; }
	return result;
}

//
Matrix4x4 operator*(const Matrix4x4& lhs_, const Matrix4x4& rhs_)
{
	float zeros[_sz * _sz] = { 0 };
	Matrix4x4 result(zeros);

	for (size_t i = 0; i < _sz * _sz; ++i)
	{
		for (size_t j = 0; j < _sz; ++j)
		{ result.m[i] += lhs_.m[(i / _sz) * _sz + j] * rhs_.m[j * _sz + i % _sz]; }
	}
	return result;
}

//
Vector3D operator*(const Matrix4x4& mtx_, const Vector3D& rhs_)
{
	const size_t n = 3; // # of dimensions of vector
	Vector3D result(0, 0, 0);

	// applying effect of upper-left 3x3 submatrix of mtx_
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{ result.m[i] += mtx_.m[i * _sz + j] * rhs_.m[j]; }
	}

	// translation
	for (size_t i = 0; i < n; ++i)
	{ result.m[i] += mtx_.m[i * _sz + (_sz - 1)]; }
	return result;
}

//
Matrix4x4 Mtx44Identity()
{
	Matrix4x4 result;
	for (size_t i = 0; i < _sz; ++i)
	{
		for (size_t j = 0; j < _sz; ++j)
		{ result.m[i * _sz + j] = (i == j) ? 1.0f : 0.0f; }
	}
	return result;
}

//
Matrix4x4 Mtx44Translate(const float x_, const float y_, const float z_)
{
	Matrix4x4 result = Mtx44Identity();
	result.a03 = x_;
	result.a13 = y_;
	result.a23 = z_;
	return result;
}

//
Matrix4x4 Mtx44Scale(const float x_, const float y_, const float z_)
{
	Matrix4x4 result = Mtx44Identity();
	result.a00 = x_;
	result.a11 = y_;
	result.a22 = z_;
	return result;
}

//
Matrix4x4 Mtx44RotRad(const Vector3D axis_, const float radians_)
{
	Matrix4x4 result = Mtx44Identity();
	// e1 rotation
	if (axis_ == -e1_3D)
	{ return Mtx44RotRad(e1_3D, -radians_); }
	if (axis_ == e1_3D)
	{
		result.a11 = result.a22 = cosf(radians_);
		result.a21 = sinf(radians_);
		result.a12 = -result.a21;
		return result;
	}

	// e2 rotation
	if (axis_ == -e2_3D)
	{ return Mtx44RotRad(e2_3D, -radians_); }
	if (axis_ == e2_3D)
	{
		result.a00 = result.a22 = cosf(radians_);
		result.a02 = sinf(radians_);
		result.a20 = -result.a02;
		return result;
	}

	// e3 rotation
	if (axis_ == -e3_3D)
	{ return Mtx44RotRad(e3_3D, -radians_); }
	if (axis_ == e3_3D)
	{
		result.a00 = result.a11 = cosf(radians_);
		result.a10 = sinf(radians_);
		result.a01 = -result.a10;
		return result;
	}

	// general rotation
	const float a = axis_.x, b = axis_.y, c = axis_.z;
	const float alpha = sinf(radians_), beta = cosf(radians_), gamma = 1 - beta;
	const Matrix4x4 rotMtx
	{
		gamma * a * a + beta, gamma * a * b - c * alpha, gamma * a * c + b * alpha, 0,
		gamma * a * b + c * alpha, gamma * b * b + beta, gamma * b * c - a * alpha, 0,
		gamma * a * c - b * alpha, gamma * b * c + a * alpha, gamma * c * c + beta, 0,
		0, 0, 0, 1
	};
	return result = rotMtx;
}

//
Matrix4x4 Mtx44RotDeg(const Vector3D axis_, const float degrees_)
{ return Mtx44RotRad(axis_, static_cast<float>(degrees_ / 180.0f * M_PI)); }

//
Matrix4x4 Mtx44Shear(const Vector3D& shear_, const Vector3D& normal_)
{
	const float x = Vector3DDotProduct(shear_, normal_);
	if (x <= -EPSILON || EPSILON <= x)
	{ throw "Normal and Shear vectors are not perpendicular in Mtx44Shear()"; }
	// v' = v + (normal dot v) * shear
	const Vector3D e1Prime = e1_3D + Vector3DDotProduct(normal_, e1_3D) * shear_;
	const Vector3D e2Prime = e2_3D + Vector3DDotProduct(normal_, e2_3D) * shear_;
	const Vector3D e3Prime = e3_3D + Vector3DDotProduct(normal_, e3_3D) * shear_;
	Matrix4x4 result = Mtx44Identity();
	for (size_t i{ 0 }; i < _sz - 1; ++i)
	{
		result.m2[i][0] = e1Prime.m[i];
		result.m2[i][1] = e2Prime.m[i];
		result.m2[i][2] = e3Prime.m[i];
	}
	return result;
}

//
Matrix4x4 Mtx44Proj(const Vector3D& normal_)
{
	// v' = v - proj(normal)v
	const Vector3D e1Prime = e1_3D - Vector3DProj(normal_, e1_3D);
	const Vector3D e2Prime = e2_3D - Vector3DProj(normal_, e2_3D);
	const Vector3D e3Prime = e3_3D - Vector3DProj(normal_, e3_3D);
	Matrix4x4 result = Mtx44Identity();
	for (size_t i{ 0 }; i < _sz - 1; ++i)
	{
		result.m2[i][0] = e1Prime.m[i];
		result.m2[i][1] = e2Prime.m[i];
		result.m2[i][2] = e3Prime.m[i];
	}
	return result;
}

//
Matrix4x4 Mtx44Transpose(const Matrix4x4& mtx_)
{
	Matrix4x4 result = Mtx44Identity();
	for (size_t i = 0; i < _sz; ++i)
	{
		for (size_t j = 0; j < _sz; ++j)
		{ result.m[i * _sz + j] = mtx_.m[j * _sz + i]; }
		// swapped the i and j for mtx_
	}
	return result;
}

//
Matrix4x4 Mtx44Inverse(Matrix4x4* result_, float* determinant_, const Matrix4x4& mtx_)
{
	return {};
}
