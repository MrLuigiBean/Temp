#pragma once
#ifndef COLLISION_DETECTION_HPP_
#define COLLISION_DETECTION_HPP_

#include "Types.hpp"

/* STATIC INTERACTIONS */

// 
bool CDStatic_CirclePoint(const Circle circle_, const Pt2 point_);

// 
bool CDStatic_RectPoint(const Rect rect_, const Pt2 point_);

// 
bool CDStatic_CircleCircle(const Circle circle_0_, const Circle circle_1_);

// 
bool CDStatic_RectRect_AABB(const Rect rect_0_, const Rect rect_1_);

//
bool CDStatic_CircleRect(const Circle circle_, const Rect rect_);

//
bool CDStatic_CircleRay(const Circle circle_, const Ray ray_, float& inter_time_);

/* DYNAMIC INTERACTIONS */

//
bool CDDynamic_CirclePoint(const Circle circle_, const Vec2 circle_vel_, const Pt2 point_, const Vec2 point_vel_);

//
bool CDDynamic_RectPoint(const Rect rect_, const Vec2 rect_vel_, const Pt2 point_, const Vec2 point_vel_);

//
bool CDDynamic_CircleCircle(const Circle circle_0_, const Vec2 circle_vel_0_, const Circle circle_1_, const Vec2 circle_vel_1_,
	Pt2& inter_pt_A_, Pt2& inter_pt_B_, float& inter_time_);

#endif // COLLISION_DETECTION_HPP_
