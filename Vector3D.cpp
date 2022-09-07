//
#include "Vector3D.hpp"
#include <utility> // std::swap(), std::sqrt()

constexpr float EPSILON = 0.0001f;

//
Vector3D::Vector3D(const float x_, const float y_, const float z_) :
x{ x_ }, y{ y_ }, z{ z_ }
{ /* empty by design */ }

//
Vector3D& Vector3D::operator=(const Vector3D& rhs_)
{
	// copy swap algorithm
	Vector3D temp{ rhs_ };
	Swap(temp);
	return *this;
}

//
Vector3D& Vector3D::operator+=(const Vector3D& rhs_)
{ return *this = *this + rhs_; }

//
Vector3D& Vector3D::operator-=(const Vector3D& rhs_)
{ return *this = *this - rhs_; }

//
Vector3D& Vector3D::operator*=(const float rhs_)
{ return *this = *this * rhs_; }

//
Vector3D& Vector3D::operator/=(const float rhs_)
{ return *this = *this / rhs_; }

//
Vector3D Vector3D::operator-() const
{ return { x * -1, y * -1, z * -1 }; }

//
bool Vector3D::operator==(const Vector3D& rhs_) const
{
	return
		-EPSILON <= x - rhs_.x && x - rhs_.x <= EPSILON &&
		-EPSILON <= y - rhs_.y && y - rhs_.y <= EPSILON &&
		-EPSILON <= z - rhs_.z && z - rhs_.z <= EPSILON;
}

//
float Vector3D::Length() const
{ return sqrtf(LengthSq()); }

//
float Vector3D::LengthSq() const
{ return x * x + y * y + z * z; }

//
void Vector3D::Swap(Vector3D& rhs_)
{ std::swap((*this).m, rhs_.m); }

//
Vector3D operator+(const Vector3D& lhs_, const Vector3D& rhs_)
{ return { lhs_.x + rhs_.x, lhs_.y + rhs_.y, lhs_.z + rhs_.z }; }

//
Vector3D operator-(const Vector3D& lhs_, const Vector3D& rhs_)
{ return { lhs_.x - rhs_.x, lhs_.y - rhs_.y, lhs_.z - rhs_.z }; }

//
Vector3D operator*(const Vector3D& lhs_, const float rhs_)
{ return { lhs_.x * rhs_, lhs_.y * rhs_, lhs_.z * rhs_ }; }

//
Vector3D operator*(const float lhs_, const Vector3D& rhs_)
{ return { lhs_ * rhs_.x, lhs_ * rhs_.y, lhs_ * rhs_.z }; }

//
Vector3D operator/(const Vector3D& lhs_, const float rhs_)
{
	if (-EPSILON <= rhs_ && rhs_ <= EPSILON)
	{ throw "Division by 0 in operator/ for Vector3D and float"; }
	return { lhs_.x / rhs_, lhs_.y / rhs_, lhs_.z / rhs_ };
}

//
Vector3D Vector3DNormalize(const Vector3D& vec_)
{
	const float magnitude = vec_.Length();
	if (-EPSILON <= magnitude && magnitude <= EPSILON)
	{ throw "Division by 0 in Vector3DNormalize()"; }
	return { vec_.x / magnitude, vec_.y / magnitude, vec_.z / magnitude };
}

//
float Vector3DDistance(const Vector3D& vec_0_, const Vector3D& vec_1_)
{ return sqrtf(Vector3DSquaredDistance(vec_0_, vec_1_)); }

//
float Vector3DSquaredDistance(const Vector3D& vec_0_, const Vector3D& vec_1_)
{ return (vec_0_.x - vec_1_.x) * (vec_0_.x - vec_1_.x) + (vec_0_.y - vec_1_.y) * (vec_0_.y - vec_1_.y) + (vec_0_.z - vec_1_.z) * (vec_0_.z - vec_1_.z); }

//
float Vector3DDotProduct(const Vector3D& vec_0_, const Vector3D& vec_1_)
{ return vec_0_.x * vec_1_.x + vec_0_.y * vec_1_.y + vec_0_.z * vec_1_.z; }

//
float Vector3DCrossProductMag(const Vector3D& vec_0_, const Vector3D& vec_1_)
{ return Vector3DCrossProduct(vec_0_, vec_1_).Length(); }

//
Vector3D Vector3DCrossProduct(const Vector3D& vec_0_, const Vector3D& vec_1_)
{ return { vec_0_.y * vec_1_.z - vec_0_.z * vec_1_.y, vec_0_.z * vec_1_.x - vec_0_.x * vec_1_.z, vec_0_.x * vec_1_.y - vec_0_.y * vec_1_.x }; }

//
float Vector3DProjLength(const Vector3D& base_, const Vector3D& vec_)
{ return Vector3DDotProduct(Vector3DNormalize(base_), vec_); }

//
Vector3D Vector3DProj(const Vector3D& base_, const Vector3D& vec_)
{ return Vector3DProjLength(base_, vec_) * Vector3DNormalize(base_); }

//
Vector3D Vector3DPerpProj(const Vector3D& base_, const Vector3D& vec_)
{ return vec_ - Vector3DProj(base_, vec_); }
