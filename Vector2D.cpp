//
#include "Vector2D.hpp"
#include <corecrt_math_defines.h> // M_PI
#include <utility> // std::swap(), std::sqrt()

constexpr float EPSILON = 0.0001f;

//
Vector2D::Vector2D(const float x_, const float y_) : x{ x_ }, y{ y_ }
{ /* empty by design */ }

//
Vector2D& Vector2D::operator=(const Vector2D& rhs_)
{
	Vec2 temp{ rhs_ };
	Swap(temp);
	return *this;
}

//
Vector2D& Vector2D::operator+=(const Vector2D& rhs_)
{ return *this = *this + rhs_; }

//
Vector2D& Vector2D::operator-=(const Vector2D& rhs_)
 {	return *this = *this - rhs_; }

//
Vector2D& Vector2D::operator*=(const float rhs_)
{ 	return *this = *this * rhs_; }

//
Vector2D& Vector2D::operator/=(const float rhs_)
{ return *this = *this / rhs_; }

//
Vector2D Vector2D::operator-() const
{ return { x * -1, y * -1 }; }

//
bool Vector2D::operator==(const Vector2D& rhs_) const
{
	return
		-EPSILON <= x - rhs_.x && x - rhs_.x <= EPSILON &&
		-EPSILON <= y - rhs_.y && y - rhs_.y <= EPSILON;
}

//
float Vector2D::Length() const
{ return sqrtf(LengthSq()); }

//
float Vector2D::LengthSq() const
{ return x * x + y * y; }

//
void Vector2D::Swap(Vector2D& rhs_)
{ std::swap((*this).m, rhs_.m); }

//
Vector2D operator+(const Vector2D& lhs_, const Vector2D& rhs_)
{ return { lhs_.x + rhs_.x, lhs_.y + rhs_.y }; }

//
Vector2D operator-(const Vector2D& lhs_, const Vector2D& rhs_)
{ return { lhs_.x - rhs_.x, lhs_.y - rhs_.y }; }

//
Vector2D operator*(const Vector2D& lhs_, const float rhs_)
{ return { lhs_.x * rhs_, lhs_.y * rhs_ }; }

//
Vector2D operator*(const float lhs_, const Vector2D& rhs_)
{ return { lhs_ * rhs_.x, lhs_ * rhs_.y }; }

//
Vector2D operator/(const Vector2D& lhs_, const float rhs_)
{
	if (-EPSILON <= rhs_ && rhs_ <= EPSILON)
	{ throw "Division by 0 in Vector2D operator/"; }
	return { lhs_.x / rhs_, lhs_.y / rhs_ };
}

//
Vector2D Vector2DNormalize(const Vector2D& vec_)
{
	const float magnitude = vec_.Length();
	if (-EPSILON <= magnitude && magnitude <= EPSILON)
	{ throw "Division by 0 in Vector2DNormalize()"; }
	return { vec_.x / magnitude, vec_.y / magnitude };
}

//
float Vector2DDistance(const Vector2D& vec_0_, const Vector2D& vec_1_)
{ return sqrtf(Vector2DSquaredDistance(vec_0_, vec_1_)); }

//
float Vector2DSquaredDistance(const Vector2D& vec_0_, const Vector2D& vec_1_)
{ return (vec_0_.x - vec_1_.x) * (vec_0_.x - vec_1_.x) + (vec_0_.y - vec_1_.y) * (vec_0_.y - vec_1_.y); }

//
float Vector2DDotProduct(const Vector2D& vec_0_, const Vector2D& vec_1_)
{ return vec_0_.x * vec_1_.x + vec_0_.y * vec_1_.y; }

//
float Vector2DCrossProductMag(const Vector2D& vec_0_, const Vector2D& vec_1_)
{ return vec_0_.x * vec_1_.y - vec_0_.y * vec_1_.x; }

//
float Vector2DProjLength(const Vector2D& base_, const Vector2D& vec_)
{ return Vector2DDotProduct(Vector2DNormalize(base_), vec_); }

//
Vector2D Vector2DProj(const Vector2D& base_, const Vector2D& vec_)
{ return Vector2DProjLength(base_, vec_) * Vector2DNormalize(base_); }

//
Vector2D Vector2DPerpProj(const Vector2D& base_, const Vector2D& vec_)
{ return vec_ - Vector2DProj(base_, vec_); }

//
Vector2D Vector2DFromRadians(float radians_)
{ return { cosf(radians_),sinf(radians_) }; }

//
Vector2D Vector2DFromDegrees(float degrees_)
{ return Vector2DFromRadians(static_cast<float>(degrees_ / 180.0f * M_PI)); }
