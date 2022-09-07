#pragma once
#ifndef TYPES_HPP_
#define TYPES_HPP_

#include "Vector2D.hpp"

struct AABB; // just a forward declaration

struct LineSegment
{
	Pt2	pt0;
	Pt2	pt1;
	Vec2 normal;
	LineSegment(Pt2 pos_, float scale_, float dir_);	
};

struct Circle
{
	Pt2	center;
	float radius;
	float mass{ 1.0f };
};

struct Ray
{
	Pt2 pt;
	Vec2 dir;
};

struct Rect
{
	Pt2 center;
	float width;
	float height;
	Rect(const AABB aabb_);
};

struct AABB
{
	Pt2 min;
	Pt2 max;
	AABB(const Rect rect_);
};

#endif // TYPES_HPP_
