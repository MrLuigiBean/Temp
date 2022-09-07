//
#include "Types.hpp"
#include "Matrix3x3.hpp"

LineSegment::LineSegment(Pt2 pos_, float scale_, float dir_)
{
	Pt2 p0(0, 0), p1(0, 0);
	Mtx33 rot = Mtx33RotRad(dir_);
	// scale
	p0.x -= scale_ / 2.0f;
	p1.x += scale_ / 2.0f;
	// rotate
	p0 = rot * p0;
	p1 = rot * p1;
	// translate
	p0 += pos_;
	p1 += pos_;

	// assignment of variables
	pt0 = p0;
	pt1 = p1;
	const Vec2 vec = pt1 - pt0;
	Vec2 normal_temp;
	normal_temp.x = vec.y;
	normal_temp.y = -vec.x;
	normal = Vector2DNormalize(normal_temp);
}

Rect::Rect(const AABB aabb)
{
	width = aabb.max.x - aabb.min.x;
	height = aabb.max.y - aabb.min.y;
	center.x = aabb.min.x + width / 2;
	center.y = aabb.min.y + height / 2;
}

AABB::AABB(const Rect rect)
{
	const Vec2 temp{ rect.width / 2,rect.height / 2 };
	min = rect.center - temp;
	max = rect.center + temp;
}

