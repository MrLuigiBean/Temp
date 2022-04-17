//
#include "Vector2D.hpp"
#include <corecrt_math_defines.h> // M_PI
#include <utility> // std::swap(), std::sqrt()

constexpr float EPSILON = 0.0001f;

//
Vector2D::Vector2D(const float x, const float y) : x{ x }, y{ y }
{ /* empty by design */ }

Vector2D& Vector2D::operator=(const Vector2D& rhs)
{
	Vec2 temp{ rhs };
	Swap(temp);
	return *this;
}

//
Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{ return *this = *this + rhs; }

//
Vector2D& Vector2D::operator-=(const Vector2D& rhs)
 {	return *this = *this - rhs; }

//
Vector2D& Vector2D::operator*=(const float rhs)
{ 	return *this = *this * rhs; }

//
Vector2D& Vector2D::operator/=(const float rhs)
{ return *this = *this / rhs; }

//
Vector2D Vector2D::operator-() const
{ return { x * -1, y * -1 }; }

//
bool Vector2D::operator==(const Vector2D& rhs) const
{
	return
		-EPSILON <= x - rhs.x && x - rhs.x <= EPSILON &&
		-EPSILON <= y - rhs.y && y - rhs.y <= EPSILON;
}

//
float Vector2D::Length() const
{ return sqrtf(LengthSq()); }

//
float Vector2D::LengthSq() const
{ return x * x + y * y; }

//
void Vector2D::Swap(Vector2D& rhs)
{ std::swap((*this).m, rhs.m); }

//
Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{ return { lhs.x + rhs.x, lhs.y + rhs.y }; }

//
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{ return { lhs.x - rhs.x, lhs.y - rhs.y }; }

//
Vector2D operator*(const Vector2D& lhs, const float rhs)
{ return { lhs.x * rhs, lhs.y * rhs }; }

//
Vector2D operator*(const float lhs, const Vector2D& rhs)
{ return { lhs * rhs.x, lhs * rhs.y }; }

//
Vector2D operator/(const Vector2D& lhs, const float rhs)
{
	if (-EPSILON <= rhs && rhs <= EPSILON)
	{ throw "Division by 0 in Vector2D operator/"; }
	return { lhs.x / rhs, lhs.y / rhs };
}

//
Vector2D Vector2DNormalize(const Vector2D& vec)
{
	const float magnitude = vec.Length();
	if (-EPSILON <= magnitude && magnitude <= EPSILON)
	{ throw "Division by 0 in Vector2DNormalize()"; }
	return { vec.x / magnitude, vec.y / magnitude };
}

//
float Vector2DDistance(const Vector2D& v0, const Vector2D& v1)
{ return sqrtf(Vector2DSquaredDistance(v0, v1)); }

//
float Vector2DSquaredDistance(const Vector2D& v0, const Vector2D& v1)
{ return (v0.x - v1.x) * (v0.x - v1.x) + (v0.y - v1.y) * (v0.y - v1.y); }

//
float Vector2DDotProduct(const Vector2D& v0, const Vector2D& v1)
{ return v0.x * v1.x + v0.y * v1.y; }

//
float Vector2DCrossProductMag(const Vector2D& v0, const Vector2D& v1)
{ return v0.x * v1.y - v0.y * v1.x; }

//
float Vector2DProjLength(const Vector2D& base, const Vector2D& vec)
{ return Vector2DDotProduct(Vector2DNormalize(base), vec); }

//
Vector2D Vector2DProj(const Vector2D& base, const Vector2D& vec)
{ return Vector2DProjLength(base, vec) * Vector2DNormalize(base); }

//
Vector2D Vector2DPerpProj(const Vector2D& base, const Vector2D& vec)
{ return vec - Vector2DProj(base, vec); }

//
Vector2D Vector2DFromRadians(float radians)
{ return { cosf(radians),sinf(radians) }; }

//
Vector2D Vector2DFromDegrees(float degrees)
{ return Vector2DFromRadians(static_cast<float>(degrees / 180.0f * M_PI)); }
