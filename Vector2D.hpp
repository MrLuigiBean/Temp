//
#pragma once
#ifndef VECTOR2D_H_
#define VECTOR2D_H_

//
typedef union Vector2D
{
	// some warning about a nameless struct
	// but it's way more convenient this way :(
	struct
	{ float x, y; };

	float m[2]{};

	/* Constructors */

	//
	Vector2D() = default;

	//
	Vector2D(float x_, float y_);

	/* Assignment Operators */

	//
	Vector2D& operator=(const Vector2D& rhs_);

	//
	Vector2D& operator+=(const Vector2D& rhs_);

	//
	Vector2D& operator-=(const Vector2D& rhs_);

	//
	Vector2D& operator*=(float rhs_);

	//
	Vector2D& operator/=(float rhs_);

	/* Unary Operators */

	//
	Vector2D operator-() const;

	/* Comparison Operators */

	//
	bool operator==(const Vector2D& rhs_) const;

	/* Others */

	//
	float Length() const;

	//
	float LengthSq() const;

	//
	void Swap(Vector2D& rhs_);

} Vector2D, Vec2, Point2D, Pt2;

//
Vector2D operator+(const Vector2D& lhs_, const Vector2D& rhs_);

//
Vector2D operator-(const Vector2D& lhs_, const Vector2D& rhs_);

//
Vector2D operator*(const Vector2D& lhs_, float rhs_);

//
Vector2D operator*(float lhs_, const Vector2D& rhs_);

//
Vector2D operator/(const Vector2D& lhs_, float rhs_);

//
Vector2D Vector2DNormalize(const Vector2D& vec_);

//
float Vector2DDistance(const Vector2D& vec_0_, const Vector2D& vec_1_);

//
float Vector2DSquaredDistance(const Vector2D& vec_0_, const Vector2D& vec_1_);

//
float Vector2DDotProduct(const Vector2D& vec_0_, const Vector2D& vec_1_);

//
float Vector2DCrossProductMag(const Vector2D& vec_0_, const Vector2D& vec_1_);

//
float Vector2DProjLength(const Vector2D& base_, const Vector2D& vec_);

//
Vector2D Vector2DProj(const Vector2D& base_, const Vector2D& vec_);

//
Vector2D Vector2DPerpProj(const Vector2D& base_, const Vector2D& vec_);

//
Vector2D Vector2DFromRadians(float radians_);

//
Vector2D Vector2DFromDegrees(float degrees_);

#endif // VECTOR2D_H_
