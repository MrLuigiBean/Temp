//
#include "Vector3D.hpp"
#include <utility> // std::swap(), std::sqrt()

constexpr float EPSILON = 0.0001f;

//
Vector3D::Vector3D(const float x, const float y, const float z) :
x{ x }, y{ y }, z{ z }
{ /* empty by design */ }

//
Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	Vector3D temp{ rhs };
	Swap(temp);
	return *this;
}

//
Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{ return *this = *this + rhs; }

//
Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{ return *this = *this - rhs; }

//
Vector3D& Vector3D::operator*=(const float rhs)
{ return *this = *this * rhs; }

//
Vector3D& Vector3D::operator/=(const float rhs)
{ return *this = *this / rhs; }

//
Vector3D Vector3D::operator-() const
{ return { x * -1, y * -1, z * -1 }; }

//
bool Vector3D::operator==(const Vector3D & rhs) const
{
	return
		-EPSILON <= x - rhs.x && x - rhs.x <= EPSILON &&
		-EPSILON <= y - rhs.y && y - rhs.y <= EPSILON &&
		-EPSILON <= z - rhs.z && z - rhs.z <= EPSILON;
}

//
float Vector3D::Length() const
{ return sqrtf(LengthSq()); }

//
float Vector3D::LengthSq() const
{ return x * x + y * y + z * z; }

//
void Vector3D::Swap(Vector3D& rhs)
{ std::swap((*this).m, rhs.m); }

//
Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs)
{ return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z }; }

//
Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs)
{ return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z }; }

//
Vector3D operator*(const Vector3D& lhs, const float rhs)
{ return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs }; }

//
Vector3D operator*(const float lhs, const Vector3D& rhs)
{ return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z }; }

//
Vector3D operator/(const Vector3D& lhs, const float rhs)
{
	if (-EPSILON <= rhs && rhs <= EPSILON)
	{ throw "Division by 0 in Vector3D operator/"; }
	return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
}

//
Vector3D Vector3DNormalize(const Vector3D& vec)
{
	const float magnitude = vec.Length();
	if (-EPSILON <= magnitude && magnitude <= EPSILON)
	{ throw "Division by 0 in Vector3DNormalize()"; }
	return { vec.x / magnitude, vec.y / magnitude, vec.z / magnitude };
}

//
float Vector3DDistance(const Vector3D& v1, const Vector3D& v2)
{ return sqrtf(Vector3DSquaredDistance(v1, v2)); }

//
float Vector3DSquaredDistance(const Vector3D& v1, const Vector3D& v2)
{ return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z); }

//
float Vector3DDotProduct(const Vector3D& v1, const Vector3D& v2)
{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

//
float Vector3DCrossProductMag(const Vector3D& v1, const Vector3D& v2)
{ return Vector3DCrossProduct(v1, v2).Length(); }

//
Vector3D Vector3DCrossProduct(const Vector3D& v1, const Vector3D& v2)
{ return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x }; }

//
float Vector3DProjLength(const Vector3D& base, const Vector3D& vec)
{ return Vector3DDotProduct(Vector3DNormalize(base), vec); }

//
Vector3D Vector3DProj(const Vector3D& base, const Vector3D& vec)
{ return Vector3DProjLength(base, vec) * Vector3DNormalize(base); }

//
Vector3D Vector3DPerpProj(const Vector3D& base, const Vector3D& vec)
{ return vec - Vector3DProj(base, vec); }
