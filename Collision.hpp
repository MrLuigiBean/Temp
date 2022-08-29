/*
#pragma once
#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include "Vector2D.hpp"

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

// INTERSECTION FUNCTIONS
	//Circle data - input
	//End circle position - input
	//Line segment - input
	//Intersection point - output
	//Normal vector at collision time - output
	//Intersection time ti - output
	//The last parameter is new - for Extra Credits: true = check collision with line segment edges
int CollisionIntersection_CircleLineSegment(const Circle& circle, const Pt2& ptEnd, const LineSegment& lineSeg,
	Pt2& interPt, Vec2& normalAtCollision, float& interTime, bool& checkLineEdges);

// Extra credits
	//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	//Circle data - input
	//End circle position - input
	//Line segment - input
	//Intersection point - output
	//Normal vector at collision time - output
	//Intersection time ti - output
int CheckMovingCircleToLineEdge(bool withinBothLines, const Circle& circle, const Pt2& ptEnd,
	const LineSegment& lineSeg, Pt2& interPt, Vec2& normalAtCollision, float& interTime);

// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
// In the case of "dynamic circle vs static pillar", velB will be 0.0f

	//CircleA data - input
	//CircleA velocity - input
	//CircleB data - input
	//CircleA velocity - input
	//Intersection point of CircleA at collision time - output
	//Intersection point of CircleB at collision time - output
	//intersection time - output
int CollisionIntersection_CircleCircle(const Circle& circleA, const Vec2& velA,
	const Circle& circleB, const Vec2& velB, Pt2& interPtA, Pt2& interPtB, float& interTime);

// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
// this is a helper function to be used inside "CollisionIntersection_CircleCircle" function
// it is checking collision a moving dot vs a static circle

	//A ray containing the data of the moving dot - input
	//Static circle data - input
	//Intersection time - output
bool CollisionIntersection_RayCircle(const Ray& ray, const Circle& circle, float& interTime);

// RESPONSE FUNCTIONS
	//Intersection position of the circle - input
	//Normal vector of reflection on collision time - input
	//Final position of the circle after reflection - output
	//Normalized reflection vector direction - output
void CollisionResponse_CircleLineSegment(const Pt2& ptInter, const Vec2& normal,
	Pt2& ptEnd, Vec2& reflected);

//Normal vector of reflection on collision time - input
//Intersection time - input
//Starting position of the circle - input
//Intersection position of the circle - input
//Final position of the circle after reflection - output
//Normalized reflection vector - output
void CollisionResponse_CirclePillar(const Vec2& normal, const float& interTime, const Pt2& ptStart,
	const Pt2& ptInter, Pt2& ptEnd, Vec2& reflectedVectorNormalized);

// Extra credits
	//Normal vector of reflection on collision time - input
	//Intersection time - input
	//Velocity of CircleA - input
	//Mass of CircleA - input
	//Intersection position of circle A at collision time - input
	//Velocity of CircleB - input
	//Mass of CircleB - input
	//Intersection position of circle B at collision time - input
	//Non-Normalized reflected vector of Circle A - output
	//Final position of the circle A after reflection - output
	//Non-Normalized reflected vector of Circle B - output
	//Final position of the circle B after reflection - output
void CollisionResponse_CircleCircle(Vec2& normal, const float interTime,
	Vec2& velA, const float& massA, Pt2& interPtA,
	Vec2& velB, const float& massB, Pt2& interPtB,
	Vec2& reflectedVectorA, Pt2& ptEndA,
	Vec2& reflectedVectorB, Pt2& ptEndB);

#endif // COLLISION_HPP_
*/