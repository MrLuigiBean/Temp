//
#include "CollisionDetection.hpp"

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
	const float combinedSqRadius = (circle1.m_radius + circle2.m_radius) * (circle1.m_radius + circle2.m_radius);
	const float distSq = Vector2DDotProduct(circle1.m_center - circle2.m_center, circle1.m_center - circle2.m_center);
	return combinedSqRadius > distSq;
}

bool CDStatic_RectRect(const Rect rect1, const Rect rect2)
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
