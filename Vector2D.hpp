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
	Vector2D(float x, float y);

	/* Assignment operators */

	//
	Vector2D& operator=(const Vector2D& rhs);

	//
	Vector2D& operator+=(const Vector2D& rhs);

	//
	Vector2D& operator-=(const Vector2D& rhs);

	//
	Vector2D& operator*=(float rhs);

	//
	Vector2D& operator/=(float rhs);

	/* Unary operators */

	//
	Vector2D operator-() const;

	/* Others */

	//
	float Length() const;

	//
	float LengthSq() const;

	//
	void Swap(Vector2D& rhs);

} Vector2D, Vec2, Point2D, Pt2;

//
Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);

//
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);

//
Vector2D operator*(const Vector2D& lhs, float rhs);

//
Vector2D operator*(float lhs, const Vector2D& rhs);

//
Vector2D operator/(const Vector2D& lhs, float rhs);

//
Vector2D Vector2DNormalize(const Vector2D& vec);

//
float Vector2DDistance(const Vector2D& v0, const Vector2D& v1);

//
float Vector2DSquaredDistance(const Vector2D& v0, const Vector2D& v1);

//
float Vector2DDotProduct(const Vector2D& v0, const Vector2D& v1);

//
float Vector2DCrossProductMag(const Vector2D& v0, const Vector2D& v1);

//
float Vector2DProjLength(const Vector2D& base, const Vector2D& vec);

//
Vector2D Vector2DProj(const Vector2D& base, const Vector2D& vec);

//
Vector2D Vector2DPerpProj(const Vector2D& base, const Vector2D& vec);

//
Vector2D Vector2DFromRadians(float radians);

//
Vector2D Vector2DFromDegrees(float degrees);

#endif // VECTOR2D_H_
