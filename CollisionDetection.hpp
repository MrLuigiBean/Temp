#pragma once
#ifndef COLLISION_DETECTION_HPP_
#define COLLISION_DETECTION_HPP_

#include "Types.hpp"

// Static Collision Check for Circles against Points
bool CDStatic_CirclePoint(const Circle circle, const Pt2 point);

// Static Collision Check for Rectangles against Points
bool CDStatic_RectPoint(const Rect rect, const Pt2 point);

// Static Collision Check for Circles against Circles
bool CDStatic_CircleCircle(const Circle circle1, const Circle circle2);

// Static Collision Check for Rectangles against Rectangles
bool CDStatic_RectRect(const Rect rect1, const Rect rect2);

#endif // COLLISION_DETECTION_HPP_
