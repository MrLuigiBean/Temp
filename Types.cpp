//
#include "Types.hpp"
#include "Matrix3x3.hpp"

LineSegment::LineSegment(Pt2 pos, float scale, float dir)
{
	Pt2 p0(0, 0), p1(0, 0);
	Mtx33 rot = Mtx33RotRad(dir);
	// scale
	p0.x -= scale / 2.0f;
	p1.x += scale / 2.0f;
	// rotate
	p0 = rot * p0;
	p1 = rot * p1;
	// translate
	p0 += pos;
	p1 += pos;

	// assignment of variables
	m_pt0 = p0;
	m_pt1 = p1;
	const Vec2 vec = m_pt1 - m_pt0;
	Vec2 normal;
	normal.x = vec.y;
	normal.y = -vec.x;
	m_normal = Vector2DNormalize(normal);
}

Rect::Rect(const AABB aabb)
{
	m_width = aabb.m_max.x - aabb.m_min.x;
	m_height = aabb.m_max.y - aabb.m_min.y;
	m_center.x = aabb.m_min.x + m_width / 2;
	m_center.y = aabb.m_min.y + m_height / 2;
}

AABB::AABB(const Rect rect)
{
	const Vec2 temp{ rect.m_width / 2,rect.m_height / 2 };
	m_min = rect.m_center - temp;
	m_max = rect.m_center + temp;
}

