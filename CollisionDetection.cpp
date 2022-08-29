//
#include "CollisionDetection.hpp"

#include <corecrt_math.h> // sqrt()

bool CDStatic_CirclePoint(const Circle circle, const Pt2 point)
{
	return circle.m_radius > (circle.m_center - point).Length();
}

bool CDStatic_RectPoint(const Rect rect, const Pt2 point)
{
	AABB aabb(rect);
	return aabb.m_min.x <= point.x && point.x <= aabb.m_max.x &&
		aabb.m_min.y <= point.y && point.y <= aabb.m_max.y;
}

bool CDStatic_CircleCircle(const Circle circle1, const Circle circle2)
{
	const float combinedRadiusSq = (circle1.m_radius + circle2.m_radius) * (circle1.m_radius + circle2.m_radius);
	const float distSq = Vector2DDotProduct(circle1.m_center - circle2.m_center, circle1.m_center - circle2.m_center);
	return combinedRadiusSq > distSq;
}

bool CDStatic_RectRect_AABB(const Rect rect1, const Rect rect2)
{
	AABB aabb1(rect1); AABB aabb2(rect2);
	if (aabb1.m_min.x >= aabb2.m_max.x || aabb2.m_min.x >= aabb1.m_max.x ||
		aabb1.m_min.y >= aabb2.m_max.y || aabb2.m_min.y >= aabb1.m_max.y)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// SUSUSUSUSUSUSUSUS
bool CDStatic_CircleRect(const Circle circle, const Rect rect)
{
	AABB aabb(rect);
	Pt2 test = circle.m_center;

	if (circle.m_center.x < aabb.m_min.x)
		test.x = aabb.m_min.x;
	else if (circle.m_center.x > aabb.m_max.x)
		test.x = aabb.m_max.x;

	if (circle.m_center.y < aabb.m_min.y)
		test.y = aabb.m_min.y;
	else if (circle.m_center.y > aabb.m_max.y)
		test.y = aabb.m_max.y;

	if (Vector2DDotProduct(circle.m_center - test, circle.m_center - test) <= circle.m_radius * circle.m_radius)
		return true;
	return false;
}

bool CDStatic_CircleRay(const Circle circle, const Ray ray, float& interTime)
{
	Vec2 vNorm, BsC;
	vNorm = Vector2DNormalize(ray.m_dir);
	BsC = circle.m_center - ray.m_pt0;
	float m = Vector2DDotProduct(vNorm, BsC);

	// rejection tests:

	// m < 0 and Bs is outside circle
	if (m < 0 && Vector2DDotProduct(BsC, BsC) > circle.m_radius * circle.m_radius) { return 0; }

	// n^2 = |BsC|^2 - m^2
	float nSq = BsC.LengthSq() - m * m;
	// n^2 > r^2
	if (nSq > circle.m_radius * circle.m_radius) { return 0; }

	// s^2 = r^2 - n^2
	float sSq = circle.m_radius * circle.m_radius - nSq;
	// ti0 = (m-s)/|v|
	interTime = (m - sqrtf(sSq)) / ray.m_dir.Length();

	return 0 <= interTime && interTime <= 1;
}

bool CDDynamic_CirclePoint(const Circle circle, const Vec2 circleVel, const Pt2 point, const Vec2 pointVel)
{
	return false;
}

bool CDDynamic_RectPoint(const Rect rect, const Vec2 rectVel, const Pt2 point, const Vec2 pointVel)
{
	return false;
}

bool CDDynamic_CircleCircle(const Circle circle1, const Vec2 circleVel1, const Circle circle2, const Vec2 circleVel2,
	Pt2& interPtA, Pt2& interPtB, float& interTime)
{
	// make circle1 a Ray
	Ray ray;
	ray.m_pt0 = circle1.m_center;
	ray.m_dir = circleVel1 - circleVel2; // relative velocity

	// make circle2 a bigger, stationary circle
	Circle newCircle{ circle2 };
	newCircle.m_radius += circle1.m_radius;

	if (CDStatic_CircleRay(newCircle, ray, interTime))
	{
		interPtA = circle1.m_center + interTime * circleVel1;
		interPtB = circle2.m_center + interTime * circleVel2;

		return true;
	}
	return false;
}
