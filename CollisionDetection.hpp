#pragma once
#ifndef COLLISION_DETECTION_HPP_
#define COLLISION_DETECTION_HPP_

#include "Types.hpp"

/* STATIC INTERACTIONS */

// 
bool CDStatic_CirclePoint(const Circle circle, const Pt2 point);

// 
bool CDStatic_RectPoint(const Rect rect, const Pt2 point);

// 
bool CDStatic_CircleCircle(const Circle circle1, const Circle circle2);

// 
bool CDStatic_RectRect_AABB(const Rect rect1, const Rect rect2);

//
bool CDStatic_CircleRect(const Circle circle, const Rect rect);

//
bool CDStatic_CircleRay(const Circle circle, const Ray ray, float& interTime);

/* DYNAMIC INTERACTIONS */

//
bool CDDynamic_CirclePoint(const Circle circle, const Vec2 circleVel, const Pt2 point, const Vec2 pointVel);

//
bool CDDynamic_RectPoint(const Rect rect, const Vec2 rectVel, const Pt2 point, const Vec2 pointVel);

//
bool CDDynamic_CircleCircle(const Circle circle1, const Vec2 circleVel1, const Circle circle2, const Vec2 circleVel2,
	Pt2& interPtA, Pt2& interPtB, float& interTime);

#endif // COLLISION_DETECTION_HPP_
