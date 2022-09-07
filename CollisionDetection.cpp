//
#include "CollisionDetection.hpp"

#include <corecrt_math.h> // sqrt()

//
bool CDStatic_CirclePoint(const Circle circle_, const Pt2 point_)
{
	return circle_.radius > (circle_.center - point_).Length();
}

//
bool CDStatic_RectPoint(const Rect rect_, const Pt2 point_)
{
	AABB aabb(rect_);
	return aabb.min.x <= point_.x && point_.x <= aabb.max.x &&
		aabb.min.y <= point_.y && point_.y <= aabb.max.y;
}

//
bool CDStatic_CircleCircle(const Circle circle_0_, const Circle circle_1_)
{
	const float combined_radius_sq = (circle_0_.radius + circle_1_.radius) * (circle_0_.radius + circle_1_.radius);
	const float dist_sq = Vector2DDotProduct(circle_0_.center - circle_1_.center, circle_0_.center - circle_1_.center);
	return combined_radius_sq > dist_sq;
}

//
bool CDStatic_RectRect_AABB(const Rect rect_0_, const Rect rect_1_)
{
	AABB aabb_0(rect_0_); AABB aabb_1(rect_1_);
	if (aabb_0.min.x >= aabb_1.max.x || aabb_1.min.x >= aabb_0.max.x ||
		aabb_0.min.y >= aabb_1.max.y || aabb_1.min.y >= aabb_0.max.y)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// SUSUSUSUSUSUSUSUS
bool CDStatic_CircleRect(const Circle circle_, const Rect rect_)
{
	AABB aabb(rect_);
	Pt2 test = circle_.center;

	if (circle_.center.x < aabb.min.x)
		test.x = aabb.min.x;
	else if (circle_.center.x > aabb.max.x)
		test.x = aabb.max.x;

	if (circle_.center.y < aabb.min.y)
		test.y = aabb.min.y;
	else if (circle_.center.y > aabb.max.y)
		test.y = aabb.max.y;

	if (Vector2DDotProduct(circle_.center - test, circle_.center - test) <= circle_.radius * circle_.radius)
		return true;
	return false;
}

//
bool CDStatic_CircleRay(const Circle circle_, const Ray ray_, float& inter_time_)
{
	Vec2 v_normalised, BsC;
	v_normalised = Vector2DNormalize(ray_.dir);
	BsC = circle_.center - ray_.pt;
	float m = Vector2DDotProduct(v_normalised, BsC);

	// rejection tests:

	// m < 0 and Bs is outside circle
	if (m < 0 && Vector2DDotProduct(BsC, BsC) > circle_.radius * circle_.radius) { return 0; }

	// n^2 = |BsC|^2 - m^2
	float nSq = BsC.LengthSq() - m * m;
	// n^2 > r^2
	if (nSq > circle_.radius * circle_.radius) { return 0; }

	// s^2 = r^2 - n^2
	float sSq = circle_.radius * circle_.radius - nSq;
	// ti0 = (m-s)/|v|
	inter_time_ = (m - sqrtf(sSq)) / ray_.dir.Length();

	return 0 <= inter_time_ && inter_time_ <= 1;
}

//
bool CDDynamic_CirclePoint(const Circle circle_, const Vec2 circle_vel_, const Pt2 point_, const Vec2 point_vel_)
{
	return false;
}

//
bool CDDynamic_RectPoint(const Rect rect_, const Vec2 rect_vel_, const Pt2 point_, const Vec2 point_vel_)
{
	return false;
}

//
bool CDDynamic_CircleCircle(const Circle circle_0_, const Vec2 circle_vel_0_, const Circle circle_1_, const Vec2 circle_vel_1_,
	Pt2& inter_pt_A_, Pt2& inter_pt_B_, float& inter_time_)
{
	// make circle1 a Ray
	Ray ray;
	ray.pt = circle_0_.center;
	ray.dir = circle_vel_0_ - circle_vel_1_; // relative velocity

	// make circle_1_ a bigger, stationary circle
	Circle new_circle{ circle_1_ };
	new_circle.radius += circle_0_.radius;

	if (CDStatic_CircleRay(new_circle, ray, inter_time_))
	{
		inter_pt_A_ = circle_0_.center + inter_time_ * circle_vel_0_;
		inter_pt_B_ = circle_1_.center + inter_time_ * circle_vel_1_;

		return true;
	}
	return false;
}
