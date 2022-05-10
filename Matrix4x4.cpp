//
#include "Matrix4x4.hpp"
#include <algorithm> // std::swap()
#include <corecrt_math_defines.h> // M_PI

constexpr float EPSILON = 0.0001f;
static const size_t sz = 4; // # of dimensions of matrix

const Vector3D e1_3D{ 1, 0, 0 };
const Vector3D e2_3D{ 0, 1, 0 };
const Vector3D e3_3D{ 0, 0, 1 };

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
float Matrix4x4::Determinant() const
{
	return 0;
}

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
Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
	float zeros[sz * sz] = { 0 };
	Matrix4x4 result(zeros);

	for (size_t i = 0; i < sz * sz; ++i)
	{
		for (size_t j = 0; j < sz; ++j)
		{ result.m[i] += lhs.m[(i / sz) * sz + j] * rhs.m[j * sz + i % sz]; }
	}
	return result;
}

//
Vector3D operator*(const Matrix4x4& mtx, const Vector3D& rhs)
{
	const size_t n = 3; // # of dimensions of vector
	Vector3D result(0, 0, 0);

	// applying effect of upper-left 3x3 submatrix of mtx
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{ result.m[i] += mtx.m[i * sz + j] * rhs.m[j]; }
	}

	// translation
	for (size_t i = 0; i < n; ++i)
	{ result.m[i] += mtx.m[i * sz + (sz - 1)]; }
	return result;
}

//
Matrix4x4 Mtx44Identity()
{
	Matrix4x4 result;
	for (size_t i = 0; i < sz; ++i)
	{
		for (size_t j = 0; j < sz; ++j)
		{ result.m[i * sz + j] = (i == j) ? 1.0f : 0.0f; }
	}
	return result;
}

//
Matrix4x4 Mtx44Translate(const float x, const float y, const float z)
{
	Matrix4x4 result = Mtx44Identity();
	result.m03 = x;
	result.m13 = y;
	result.m23 = z;
	return result;
}

//
Matrix4x4 Mtx44Scale(const float x, const float y, const float z)
{
	Matrix4x4 result = Mtx44Identity();
	result.m00 = x;
	result.m11 = y;
	result.m22 = z;
	return result;
}

//
Matrix4x4 Mtx44RotRad(const Vector3D axis, const float radians)
{
	Matrix4x4 result = Mtx44Identity();
	// e1 rotation
	if (axis == -e1_3D)
	{ return Mtx44RotRad(e1_3D, -radians); }
	if (axis == e1_3D)
	{
		result.m11 = result.m22 = cosf(radians);
		result.m21 = sinf(radians);
		result.m12 = -result.m21;
		return result;
	}

	// e2 rotation
	if (axis == -e2_3D)
	{ return Mtx44RotRad(e2_3D, -radians); }
	if (axis == e2_3D)
	{
		result.m00 = result.m22 = cosf(radians);
		result.m02 = sinf(radians);
		result.m20 = -result.m02;
		return result;
	}

	// e3 rotation
	if (axis == -e3_3D)
	{ return Mtx44RotRad(e3_3D, -radians); }
	if (axis == e3_3D)
	{
		result.m00 = result.m11 = cosf(radians);
		result.m10 = sinf(radians);
		result.m01 = -result.m10;
		return result;
	}

	// general rotation
	const float a = axis.x, b = axis.y, c = axis.z;
	const float alpha = sinf(radians), beta = cosf(radians), gamma = 1 - beta;
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
Matrix4x4 Mtx44RotDeg(const Vector3D axis, const float degrees)
{ return Mtx44RotRad(axis, static_cast<float>(degrees / 180.0f * M_PI)); }

//
Matrix4x4 Mtx44Shear(const Vector3D& shear, const Vector3D& normal)
{
	const float x = Vector3DDotProduct(shear, normal);
	if (x <= -EPSILON || EPSILON <= x)
	{ throw "Normal and Shear vectors are not perpendicular in Mtx44Shear()"; }
	// v' = v + (normal dot v) * shear
	const Vector3D e1Prime = e1_3D + Vector3DDotProduct(normal, e1_3D) * shear;
	const Vector3D e2Prime = e2_3D + Vector3DDotProduct(normal, e2_3D) * shear;
	const Vector3D e3Prime = e3_3D + Vector3DDotProduct(normal, e3_3D) * shear;
	Matrix4x4 result = Mtx44Identity();
	for (size_t i{ 0 }; i < sz - 1; ++i)
	{
		result.m2[i][0] = e1Prime.m[i];
		result.m2[i][1] = e2Prime.m[i];
		result.m2[i][2] = e3Prime.m[i];
	}
	return result;
}

//
Matrix4x4 Mtx44Proj(const Vector3D& normal)
{
	// v' = v - proj(normal)v
	const Vector3D e1Prime = e1_3D - Vector3DProj(normal, e1_3D);
	const Vector3D e2Prime = e2_3D - Vector3DProj(normal, e2_3D);
	const Vector3D e3Prime = e3_3D - Vector3DProj(normal, e3_3D);
	Matrix4x4 result = Mtx44Identity();
	for (size_t i{ 0 }; i < sz - 1; ++i)
	{
		result.m2[i][0] = e1Prime.m[i];
		result.m2[i][1] = e2Prime.m[i];
		result.m2[i][2] = e3Prime.m[i];
	}
	return result;
}

//
Matrix4x4 Mtx44Transpose(const Matrix4x4& mtx)
{
	Matrix4x4 result = Mtx44Identity();
	for (size_t i = 0; i < sz; ++i)
	{
		for (size_t j = 0; j < sz; ++j)
		{ result.m[i * sz + j] = mtx.m[j * sz + i]; }
		// swapped the i and j for mtx
	}
	return result;
}

//
Matrix4x4 Mtx44Inverse(Matrix4x4* result, float* determinant, const Matrix4x4& mtx)
{
	return {};
}
