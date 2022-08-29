#pragma once
#ifndef TYPES_HPP_
#define TYPES_HPP_

#include "Vector2D.hpp"

struct AABB; // just a forward declaration

struct LineSegment
{
	Pt2	m_pt0;
	Pt2	m_pt1;
	Vec2 m_normal;
	LineSegment(Pt2 pos, float scale, float dir);	
};

struct Circle
{
	Pt2	m_center;
	float m_radius;
	float m_mass{ 1.0f };
};

struct Ray
{
	Pt2 m_pt0;
	Vec2 m_dir;
};

struct Rect
{
	Pt2 m_center;
	float m_width;
	float m_height;
	Rect(const AABB aabb);
};

struct AABB
{
	Pt2 m_min;
	Pt2 m_max;
	AABB(const Rect rect);
};

#endif // TYPES_HPP_
