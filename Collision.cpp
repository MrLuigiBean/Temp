/*
#include <cmath>
#include "Collision.hpp"
#include "Matrix3x3.hpp"

//
LineSegment::LineSegment(const Pt2 pos, const float scale, const float dir)
{
	Pt2 p0(0, 0), p1(0, 0);
	Mtx33 rot;
	rot = Mtx33RotRad(dir);
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
	Vec2 vec, normal;
	vec = m_pt1 - m_pt0;
	normal.x = vec.y;
	normal.y = -vec.x;
	m_normal = Vector2DNormalize(normal);
}

//
int CollisionIntersection_CircleLineSegment(const Circle& circle, const Pt2& ptEnd, const LineSegment& lineSeg, Pt2& interPt, Vec2& normalAtCollision, float& interTime, bool& checkLineEdges)
{
	(void)checkLineEdges;

	Vec2 vel = ptEnd - circle.m_center;

	float lineOfSightDP = Vector2DDotProduct(lineSeg.m_normal, circle.m_center) -
		Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0);

	if (lineOfSightDP <= -circle.m_radius)
	{
		Pt2 p0New, p1New; // simulate LNS1 line edge points
		// p0' = p0 - r * n
		p0New = lineSeg.m_pt0 - circle.m_radius * lineSeg.m_normal;
		// p1' = p1 - r * n
		p1New = lineSeg.m_pt1 - circle.m_radius * lineSeg.m_normal;

		const Vec2 velNormal{ vel.y, -vel.x };

		if (Vector2DDotProduct(velNormal, p0New - circle.m_center) *
			Vector2DDotProduct(velNormal, p1New - circle.m_center) < 0)
		{
			// ti = (n dot p0 - n dot Bs - r) / (n dot v)
			interTime = Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0) -
				Vector2DDotProduct(lineSeg.m_normal, circle.m_center) -
				circle.m_radius;
			// since n dot v is =/= 0 at this point, we can safely do this:
			interTime /= Vector2DDotProduct(lineSeg.m_normal, vel);

			if (0 <= interTime && interTime <= 1)
			{
				// Bi = Bs + ti * v
				interPt = circle.m_center + interTime * vel;
				normalAtCollision = -lineSeg.m_normal;
				return 1;
			}
		}
		else
		{ /*CheckMovingCircleToLineEdge(false); }
	}
	else if (lineOfSightDP >= circle.m_radius)
	{
		Pt2 p0New, p1New; // simulates LNS2 line edge points
		// p0' = p0 + r * n
		p0New = lineSeg.m_pt0 + circle.m_radius * lineSeg.m_normal;
		// p1' = p1 + r * n
		p1New = lineSeg.m_pt1 + circle.m_radius * lineSeg.m_normal;

		const Vec2 velNormal{ vel.y, -vel.x };

		if (Vector2DDotProduct(velNormal, p0New - circle.m_center) *
			Vector2DDotProduct(velNormal, p1New - circle.m_center) < 0)
		{
			// ti = (n dot p0 - n dot Bs + r) / (n dot v)
			interTime = Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0) -
				Vector2DDotProduct(lineSeg.m_normal, circle.m_center) +
				circle.m_radius;
			// since n dot v is =/= 0 at this point, we can safely do this:
			interTime /= Vector2DDotProduct(lineSeg.m_normal, vel);

			if (0 <= interTime && interTime <= 1)
			{
				// Bi = Bs + ti * v
				interPt = circle.m_center + interTime * vel;
				normalAtCollision = lineSeg.m_normal;
				return 1;
			}
		}
		else
		{ /*CheckMovingCircleToLineEdge(false); }
	}
	else
	{ /*CheckMovingCircleToLineEdge(true); }
	// as Bs is in between LNS1 and LNS2

	return 0; // no intersection
}

//
int CheckMovingCircleToLineEdge(bool withinBothLines, const Circle& circle, const Pt2& ptEnd, const LineSegment& lineSeg, Pt2& interPt, Vec2& normalAtCollision, float& interTime)
{
	(void)withinBothLines;
	(void)circle;
	(void)ptEnd;
	(void)lineSeg;
	(void)interPt;
	(void)normalAtCollision;
	(void)interTime;
	return 0;
}

//
int CollisionIntersection_CircleCircle(const Circle& circleA, const Vec2& velA, const Circle& circleB, const Vec2& velB, Pt2& interPtA, Pt2& interPtB, float& interTime)
{
	// make circleA a Ray
	Ray rayA;
	rayA.m_pt0 = circleA.m_center;
	rayA.m_dir = velA - velB; // relative velocity

	// make B a bigger, stationary circle
	Circle newB{ circleB };
	newB.m_radius += circleA.m_radius;

	if (CollisionIntersection_RayCircle(rayA, newB, interTime))
	{
		interPtA = circleA.m_center + interTime * velA;
		interPtB = circleB.m_center + interTime * velB;

		return 1;
	}
	return 0;
}

//
bool CollisionIntersection_RayCircle(const Ray& ray, const Circle& circle, float& interTime)
{
	Vec2 vNorm, BsC;
	vNorm = Vector2DNormalize(ray.m_dir);
	BsC = circle.m_center - ray.m_pt0;
	float m = Vector2DDotProduct(vNorm, BsC);

	// rejection tests:

	// m < 0 and Bs is outside circle
	if (m < 0 && Vector2DDotProduct(BsC, BsC) > circle.m_radius * circle.m_radius) { return false; }

	// n^2 = |BsC|^2 - m^2
	const float nSq = BsC.LengthSq() - m * m;
	// n^2 > r^2
	if (nSq > circle.m_radius * circle.m_radius) { return false; }

	// s^2 = r^2 - n^2
	const float sSq = circle.m_radius * circle.m_radius - nSq;
	// ti0 = (m-s)/|v|
	interTime = (m - sqrtf(sSq)) / ray.m_dir.Length();

	return 0 <= interTime && interTime <= 1;
}

//
void CollisionResponse_CircleLineSegment(const Pt2& ptInter, const Vec2& normal, Pt2& ptEnd, Vec2& reflected)
{
	const Vec2 penetrationVec = ptEnd - ptInter;
	ptEnd = ptInter + penetrationVec - 2 * Vector2DDotProduct(penetrationVec, normal) * normal;
	reflected = Vector2DNormalize(ptEnd - ptInter);
}

//
void CollisionResponse_CirclePillar(const Vec2& normal, const float& interTime, const Pt2& ptStart, const Pt2& ptInter, Pt2& ptEnd, Vec2& reflectedVectorNormalized)
{
	(void)interTime;
	(void)ptStart;

	const Vec2 penetrationVec = ptEnd - ptInter;
	ptEnd = ptInter + penetrationVec - 2 * Vector2DDotProduct(penetrationVec, normal) * normal;
	reflectedVectorNormalized = Vector2DNormalize(ptEnd - ptInter);
}

//
void CollisionResponse_CircleCircle(Vec2& normal, const float interTime, Vec2& velA, const float& massA, Pt2& interPtA, Vec2& velB, const float& massB, Pt2& interPtB, Vec2& reflectedVectorA, Pt2& ptEndA, Vec2& reflectedVectorB, Pt2& ptEndB)
{
	(void)normal;
	(void)interTime;
	(void)velA;
	(void)massA;
	(void)interPtA;
	(void)velB;
	(void)massB;
	(void)interPtB;
	(void)reflectedVectorA;
	(void)ptEndA;
	(void)reflectedVectorB;
	(void)ptEndB;
}
*/