#define OLD 0
#if OLD

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring> // memset

#include "Collision.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"

#define EPSILON		0.0001f
#define PI			3.14159265358f

#define TEST_VEC2 0
#define TEST_VEC3 0
#define TEST_MTX33 0
#define TEST_MTX44 0

// these functions depend on the given type have the members 'm' and 'm2'
#if 0
//
template <typename T>
void PrintVector(char const* txt, T const& vec)
{
	// don't print if there's nothing to print
	if (*txt != '\0') { printf("%s:\n", txt); }
	for (size_t i{ 0 }, sz{ std::size(vec.m) }; i < sz; ++i)
	{
		printf("|% f", vec.m[i]);
		printf("%s", i != sz - 1 ? " " : " |\n");
	}
}

//
template <typename T>
void PrintMatrix(char const* txt, T const& mtx)
{
	// don't print if there's nothing to print
	if (*txt != '\0') { printf("%s:\n", txt); }
	for (size_t i{ 0 }, sz{ std::size(mtx.m2) }; i < std::size(mtx.m); ++i)
	{
		printf("|% f", mtx.m[i]);
		printf("%s", i % sz != sz - 1 ? " " : " |\n");
	}
}
#endif

template <typename T>
void PrintVector(char const* label, T const& vec)
{
	if (*label != '\0') { printf("%s:\n", label); }
	for (size_t i{ 0 }, sz{ sizeof(T) / sizeof(float) }; i < sz; ++i)
	{
		printf("|% f", *(reinterpret_cast<float const*>(&vec) + i));
		printf("%s", i != sz - 1 ? " " : " |\n");
	}
}

// must be a square matrix!!!
template <typename T>
void PrintMatrix(char const* label, T const& mtx)
{
	// don't print if there's nothing to print
	if (*label != '\0') { printf("%s:\n", label); }
	for (size_t i{ 0 }, sz{ static_cast<size_t>(sqrt(sizeof(T) / sizeof(float))) };
		i < sizeof(T) / sizeof(float); ++i)
	{
		printf("|% f", *(reinterpret_cast<float const*>(&mtx) + i));
		printf("%s", i % sz != sz - 1 ? " " : " |\n");
	}
}

//
template <typename T>
float CompareMtx(const T& pSrc, const T& pDst)
{
	float d = 0.0f;
	for (size_t i{ 0 }; i < std::size(pSrc.m); ++i)
	{
		d += fabsf(pSrc.m[i] - pDst.m[i]);
	}
	return d;
}

//
template <typename T>
float CompareVec(const T& pSrc, const T& pDst)
{
	float d = 0.0f;
	for (size_t i{ 0 }; i < std::size(pSrc.m); ++i)
	{
		d += fabsf(pSrc.m[i] - pDst.m[i]);
	}
	return d;
}

//
int Test2D()
{
	#if TEST_VEC2
	// Testing Vector2D
	//--------------------------------------------------------------------------
	Vec2 v1, v2, v3, result;

	printf("Testing Vector2D:\n");
	printf("-----------------------------\n");

	Vec2 v4(1.0f, 2.0f);
	result.x = 1.0f;	result.y = 2.0f;
	printf("Vec2Set: \t\t%s\n",
		(CompareVec(result, v4) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Negate
	//--------------------------------------------------------------------------
	v1.x = 2.0f; v1.y = -4.0f;
	v2 = -v1;
	result.x = -2.0f;	result.y = 4.0f;
	printf("Vec2Neg: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Add
	//--------------------------------------------------------------------------
	v1.x = 2.0f; v1.y = -4.0f;
	v2.x = 1.0f; v2.y = 7.0f;
	v3 = v1 + v2;
	result.x = result.y = 3.0f;
	printf("Vec2Add 1: \t\t%s\n",
		(CompareVec(result, v3) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -4.0f;
	v2.x = 1.0f; v2.y = 7.0f;
	v1 += v2;
	result.x = result.y = 3.0f;
	printf("Vec2Add 2: \t\t%s\n",
		(CompareVec(result, v1) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Subtract
	//--------------------------------------------------------------------------
	v1.x = 2.0f; v1.y = -4.0f;
	v2.x = 1.0f; v2.y = 7.0f;
	v3 = v1 - v2;
	result.x = 1.0f;	result.y = -11.0f;
	printf("Vec2Sub 1: \t\t%s\n",
		(CompareVec(result, v3) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -4.0f;
	v2.x = 1.0f; v2.y = 7.0f;
	v1 -= v2;
	result.x = 1.0f;	result.y = -11.0f;
	printf("Vec2Sub 2: \t\t%s\n",
		(CompareVec(result, v1) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Normalize
	//--------------------------------------------------------------------------
	v1.x = 3.0f; v1.y = 4.0f;
	v2 = Vector2DNormalize(v1);
	result.x = 0.6f;	result.y = 0.8f;
	printf("Vec2Normalize: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Scale
	//--------------------------------------------------------------------------
	v1.x = 2.0f; v1.y = -5.0f;
	v2 = v1 * 3.0f;
	result.x = 6.0f;	result.y = -15.0f;
	printf("Vec2Scale 1: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -5.0f;
	v2 = 3.0f * v1;
	result.x = 6.0f;	result.y = -15.0f;
	printf("Vec2Scale 2: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -5.0f;
	v1 *= 3.0f;
	result.x = 6.0f;	result.y = -15.0f;
	printf("Vec2Scale 3: \t\t%s\n",
		(CompareVec(result, v1) < EPSILON) ? "Pass" : "Fail");

	v1.x = 6.0f;	v1.y = -15.0f;
	v2 = v1 / 3.0f;
	result.x = 2.0f; result.y = -5.0f;
	printf("Vec2Scale 4: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	v1.x = 6.0f;	v1.y = -15.0f;
	v1 /= 3.0f;
	result.x = 2.0f; result.y = -5.0f;
	printf("Vec2Scale 5: \t\t%s\n",
		(CompareVec(result, v1) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Length
	//--------------------------------------------------------------------------
	v1.x = 3.0f; v1.y = -4.0f;
	printf("Vec2Length: \t\t%s\n",
		(fabsf(v1.Length() - 5.0f) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Square Length
	//--------------------------------------------------------------------------
	v1.x = 3.0f; v1.y = -4.0f;
	printf("Vec2SquareLength: \t%s\n",
		(fabsf(v1.LengthSq() - 25.0f) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Distance
	//--------------------------------------------------------------------------
	v1.x = 2.0f;	v1.y = 3.0f;
	v2.x = 4.0f;	v2.y = -1.0f;
	printf("Vec2Distance: \t\t%s\n",
		(fabsf(Vector2DDistance(v1, v2) - 4.472136f) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Square Distance
	//--------------------------------------------------------------------------
	v1.x = 2.0f;	v1.y = 3.0f;
	v2.x = 4.0f;	v2.y = -1.0f;
	printf("Vec2SquareDistance: \t%s\n",
		(fabsf(Vector2DSquaredDistance(v1, v2) - 20.0f) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Dot Product
	//--------------------------------------------------------------------------
	v1.x = 3.0f;	v1.y = 2.0f;
	v2.x = 4.0f;	v2.y = -6.0f;
	printf("Vec2DotProduct: \t%s\n",
		(fabsf(Vector2DDotProduct(v1, v2)) < EPSILON) ? "Pass" : "Fail");

	// Vector2D Cross Product Magnitude
	//--------------------------------------------------------------------------
	v1.x = 3.0f;	v1.y = 2.0f;
	v2.x = 4.0f;	v2.y = -6.0f;
	printf("Vec2CrossProductMag: \t%s\n",
		(fabsf(Vector2DCrossProductMag(v1, v2) + 26.0f) < EPSILON) ? "Pass" : "Fail");
	#endif

	#if TEST_MTX33
	// Testing Matrix3x3
	//--------------------------------------------------------------------------
	Mtx33 id, m0, m1;
	Vec2  u;
	float d, x, y, * p;
	long  n;

	printf("\nTesting Matrix3x3:\n");
	printf("-----------------------------\n");

	// create an id matrix for reference
	memset(id.m, 0, 9 * sizeof(float));
	id.m[0] = id.m[4] = id.m[8] = 1.0f;

	// Converion constructors
	//--------------------------------------------------------------------------
	// generate an array of random numbers
	p = new float[9];
	for (int i = 0; i < 9; ++i)
		p[i] = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	memcpy(m0.m, p, 9 * sizeof(float));
	Mtx33 m2(p);
	printf("Mtx33Constructor 1: \t%s\n",
		(CompareMtx(m0, m2) < EPSILON) ? "Pass" : "Fail");

	Mtx33 m3(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	printf("Mtx33Constructor 2: \t%s\n",
		(CompareMtx(m0, m3) < EPSILON) ? "Pass" : "Fail");

	delete[]p;

	// Identity Matrix
	//--------------------------------------------------------------------------
	m0 = Mtx33Identity();
	d = CompareMtx(id, m0);
	printf("Mtx33Identity: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Translate Matrix
	//--------------------------------------------------------------------------
	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx33Translate(x, y);
	m0.a02 -= x;
	m0.a12 -= y;
	printf("Mtx33Translate: \t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Scale Matrix
	//--------------------------------------------------------------------------
	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx33Scale(x, y);
	m0.a00 /= x;
	m0.a11 /= y;

	printf("Mtx33Scale: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Concatenate Matrix
	//--------------------------------------------------------------------------
	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx33Translate(x, y);
	m1 = Mtx33Scale(x, y);
	m0 = m0 * m1;
	m0.a02 -= x;
	m0.a12 -= y;
	m0.a00 /= x;
	m0.a11 /= y;

	printf("Mtx33Concat 1: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx33Translate(x, y);
	m1 = Mtx33Scale(x, y);
	m0 = m1 * m0;
	m0.a02 -= x * x;
	m0.a12 -= y * y;
	m0.a00 /= x;
	m0.a11 /= y;

	printf("Mtx33Concat 2: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx33Translate(x, y);
	m1 = Mtx33Scale(x, y);
	m0 *= m1;
	m0.a02 -= x;
	m0.a12 -= y;
	m0.a00 /= x;
	m0.a11 /= y;

	printf("Mtx33Concat 3: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Rotation Matrix in radians
	//--------------------------------------------------------------------------
	n = (rand() % 16) + 15;
	m0 = Mtx33Identity();
	m1 = Mtx33RotRad(2.0f * PI / n);

	for (long i = 0; i < n; i++)
		m0 = m1 * m0;

	printf("Mtx33RotRad: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Rotation Matrix in degrees
	//--------------------------------------------------------------------------
	n = (rand() % 16) + 15;
	m0 = Mtx33Identity();
	m1 = Mtx33RotDeg(360.0f / n);

	for (long i = 0; i < n; i++)
		m0 = m1 * m0;

	printf("Mtx33RotDeg: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Transpose Matrix
	//--------------------------------------------------------------------------

	m0 = Mtx33RotRad(rand() / (float)(RAND_MAX) * 2.0f * PI);
	m1 = Mtx33Transpose(m0);
	m0 = m1 * m0;

	printf("Mtx33Transpose: \t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Vector Multiplication Matrix
	//--------------------------------------------------------------------------
	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	n = (rand() % 16) + 15;
	u.x = x;
	u.y = y;
	m0 = Mtx33RotRad(2.0f * PI / n);

	for (long i = 0; i < n; i++)
		u = m0 * u;

	printf("Mtx33MultVec 1: \t%s\n",
		((fabsf(u.x - x) + fabsf(u.y - y)) < EPSILON) ? "Pass" : "Fail");

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	n = (rand() % 16) + 15;
	u.x = x;
	u.y = y;
	m0 = Mtx33Translate(x, y);

	for (long i = 1; i < n; i++)
		u = m0 * u;

	printf("Mtx33MultVec 2: \t%s\n",
		((fabsf(u.x - x * n) + fabsf(u.y - y * n)) < EPSILON) ? "Pass" : "Fail");

	// Inverse Matrix
	//--------------------------------------------------------------------------
	Mtx33 mInv;
	float det = 0.0f;
	bool quit = false;

	// loop until we find an invertible matrix
	while (!quit)
	{
		x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
		y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
		m0 = Mtx33Translate(x, y);

		n = (rand() % 16) + 15;
		m1 = Mtx33RotRad(2.0f * PI / n);

		m2 = Mtx33Scale(x, y);

		m3 = m0 * m1 * m2;

		Mtx33Inverse(&mInv, &det, m3);

		if (det <= EPSILON)
			continue;

		Mtx33Inverse(&mInv, &det, mInv);

		if (det <= EPSILON)
			continue;

		printf("Mtx33Inverse: \t\t%s\n",
			(CompareMtx(mInv, m3) < EPSILON) ? "Pass" : "Fail");
		quit = true;
	}
	#endif
	return 1;
}

//
int Test3D()
{
	#if TEST_VEC3
	// Testing Vector3D
	//--------------------------------------------------------------------------
	Vec3 v1, v2, v3, result;

	printf("Testing Vector3D:\n");
	printf("-----------------------------\n");

	Vec3 v4(1.0f, 2.0f, 3.0f);
	result.x = 1.0f;	result.y = 2.0f; result.z = 3.0f;
	printf("Vec3Set: \t\t%s\n",
		(CompareVec(result, v4) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Negate
	//--------------------------------------------------------------------------
	v1.x = 2.0f; v1.y = -4.0f; v1.z = 6.0f;
	v2 = -v1;
	result.x = -2.0f;	result.y = 4.0f; result.z = -6.0f;
	printf("Vec3Neg: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Add
	//--------------------------------------------------------------------------
	v1.x = 2.0f; v1.y = -4.0f; v1.z = 5.0f;
	v2.x = 1.0f; v2.y = 7.0f; v2.z = -2.0f;
	v3 = v1 + v2;
	result.x = result.y = result.z = 3.0f;
	printf("Vec3Add 1: \t\t%s\n",
		(CompareVec(result, v3) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -4.0f; v1.z = 5.0f;
	v2.x = 1.0f; v2.y = 7.0f; v2.z = -2.0f;
	v1 += v2;
	result.x = result.y = result.z = 3.0f;
	printf("Vec3Add 2: \t\t%s\n",
		(CompareVec(result, v1) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Subtract
	//--------------------------------------------------------------------------
	v1.x = 2.0f; v1.y = -4.0f; v1.z = 0.0f;
	v2.x = 1.0f; v2.y = 7.0f; v2.z = -1.0f;
	v3 = v1 - v2;
	result.x = 1.0f;	result.y = -11.0f; result.z = 1.0f;
	printf("Vec3Sub 1: \t\t%s\n",
		(CompareVec(result, v3) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -4.0f; v1.z = 0.0f;
	v2.x = 1.0f; v2.y = 7.0f; v2.z = -1.0f;
	v1 -= v2;
	result.x = 1.0f;	result.y = -11.0f; result.z = 1.0f;
	printf("Vec3Sub 2: \t\t%s\n",
		(CompareVec(result, v1) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Normalize
	//--------------------------------------------------------------------------
	v1.x = 3.0f; v1.y = 4.0f; v1.z = 0.0f;
	v2 = Vector3DNormalize(v1);
	result.x = 0.6f;	result.y = 0.8f; result.z = 0.0f;
	printf("Vec3Normalize: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Scale
	//--------------------------------------------------------------------------
	v1.x = 2.0f; v1.y = -5.0f; v1.z = 1.0f;
	v2 = v1 * 3.0f;
	result.x = 6.0f; result.y = -15.0f; result.z = 3.0f;
	printf("Vec3Scale 1: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -5.0f; v1.z = 1.0f;
	v2 = 3.0f * v1;
	result.x = 6.0f; result.y = -15.0f; result.z = 3.0f;
	printf("Vec3Scale 2: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -5.0f; v1.z = 1.0f;
	v1 *= 3.0f;
	result.x = 6.0f; result.y = -15.0f; result.z = 3.0f;
	printf("Vec3Scale 3: \t\t%s\n",
		(CompareVec(result, v1) < EPSILON) ? "Pass" : "Fail");

	v1.x = 6.0f; v1.y = -15.0f; v1.z = 3.0f;
	v2 = v1 / 3.0f;
	result.x = 2.0f; result.y = -5.0f; result.z = 1.0f;
	printf("Vec3Scale 4: \t\t%s\n",
		(CompareVec(result, v2) < EPSILON) ? "Pass" : "Fail");

	v1.x = 6.0f; v1.y = -15.0f; v1.z = 3.0f;
	v1 /= 3.0f;
	result.x = 2.0f; result.y = -5.0f; result.z = 1.0f;
	printf("Vec3Scale 5: \t\t%s\n",
		(CompareVec(result, v1) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Length
	//--------------------------------------------------------------------------
	v1.x = 3.0f; v1.y = -4.0f; v1.z = 0.0f;
	printf("Vec3Length: \t\t%s\n",
		(fabsf(v1.Length() - 5.0f) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Square Length
	//--------------------------------------------------------------------------
	v1.x = 3.0f; v1.y = -4.0f; v1.z = 0.0f;
	printf("Vec3SquareLength: \t%s\n",
		(fabsf(v1.LengthSq() - 25.0f) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Distance
	//--------------------------------------------------------------------------
	v1.x = 2.0f;	v1.y = 3.0f; v1.z = 0.0f;
	v2.x = 4.0f;	v2.y = -1.0f; v2.z = 0.0f;
	printf("Vec3Distance: \t\t%s\n",
		(fabsf(Vector3DDistance(v1, v2) - 4.472136f) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Square Distance
	//--------------------------------------------------------------------------
	v1.x = 2.0f;	v1.y = 3.0f; v1.z = 0.0f;
	v2.x = 4.0f;	v2.y = -1.0f; v2.z = 0.0f;
	printf("Vec3SquareDistance: \t%s\n",
		(fabsf(Vector3DSquaredDistance(v1, v2) - 20.0f) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Dot Product
	//--------------------------------------------------------------------------
	v1.x = 3.0f;	v1.y = 2.0f; v1.z = 0.0f;
	v2.x = 4.0f;	v2.y = -6.0f; v2.z = 0.0f;
	printf("Vec3DotProduct: \t%s\n",
		(fabsf(Vector3DDotProduct(v1, v2)) < EPSILON) ? "Pass" : "Fail");

	// Vector3D Cross Product Magnitude
	//--------------------------------------------------------------------------
	v1.x = 3.0f;	v1.y = 2.0f; v1.z = 0.0f;
	v2.x = 4.0f;	v2.y = -6.0f; v2.z = 0.0f;
	printf("Vec3CrossProductMag: \t%s\n",
		(fabsf(Vector3DCrossProductMag(v1, v2) - 26.0f) < EPSILON) ? "Pass" : "Fail");
	#endif

	#if TEST_MTX44
	// Testing Matrix4x4
	//--------------------------------------------------------------------------
	Mtx44 id, m0, m1;
	Vec3  u;
	float d, x, y, z, * p;
	long  n;

	printf("\nTesting Matrix4x4:\n");
	printf("-----------------------------\n");

	// create an id matrix for reference
	memset(id.m, 0, 9 * sizeof(float));
	id.m[0] = id.m[5] = id.m[10] = id.m[15] = 1.0f;

	// Converion constructors
	//--------------------------------------------------------------------------
	// generate an array of random numbers
	p = new float[16];
	for (int i = 0; i < 16; ++i)
		p[i] = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	memcpy(m0.m, p, 16 * sizeof(float));
	Mtx44 m2(p);
	printf("Mtx44Constructor 1: \t%s\n",
		(CompareMtx(m0, m2) < EPSILON) ? "Pass" : "Fail");

	Mtx44 m3(p[0], p[1], p[2], p[3],
		p[4], p[5], p[6], p[7],
		p[8], p[9], p[10], p[11],
		p[12], p[13], p[14], p[15]);
	printf("Mtx44Constructor 2: \t%s\n",
		(CompareMtx(m0, m3) < EPSILON) ? "Pass" : "Fail");

	delete[]p;

	// Identity Matrix
	//--------------------------------------------------------------------------
	m0 = Mtx44Identity();
	d = CompareMtx(id, m0);
	printf("Mtx44Identity: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Translate Matrix
	//--------------------------------------------------------------------------
	// generate 3 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	z = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx44Translate(x, y, z);
	m0.a03 -= x;
	m0.a13 -= y;
	m0.a23 -= z;
	printf("Mtx44Translate: \t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Scale Matrix
	//--------------------------------------------------------------------------
	// generate 3 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	z = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx44Scale(x, y, z);
	m0.a00 /= x;
	m0.a11 /= y;
	m0.a22 /= z;

	printf("Mtx44Scale: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Concatenate Matrix
	//--------------------------------------------------------------------------
	// generate 3 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	z = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx44Translate(x, y, z);
	m1 = Mtx44Scale(x, y, z);
	m0 = m0 * m1;
	m0.a03 -= x;
	m0.a13 -= y;
	m0.a23 -= z;
	m0.a00 /= x;
	m0.a11 /= y;
	m0.a22 /= z;

	printf("Mtx44Concat 1: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// generate 3 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	z = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx44Translate(x, y, z);
	m1 = Mtx44Scale(x, y, z);
	m0 = m1 * m0;
	m0.a03 -= x * x;
	m0.a13 -= y * y;
	m0.a23 -= z * z;
	m0.a00 /= x;
	m0.a11 /= y;
	m0.a22 /= z;

	printf("Mtx44Concat 2: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// generate 3 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	z = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	m0 = Mtx44Translate(x, y, z);
	m1 = Mtx44Scale(x, y, z);
	m0 *= m1;
	m0.a03 -= x;
	m0.a13 -= y;
	m0.a23 -= z;
	m0.a00 /= x;
	m0.a11 /= y;
	m0.a22 /= z;

	printf("Mtx44Concat 3: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Rotation Matrix in radians
	//--------------------------------------------------------------------------
	n = (rand() % 16) + 15;
	m0 = Mtx44Identity();
	m1 = Mtx44RotRad(e3_3D, 2.0f * PI / n);

	for (long i = 0; i < n; i++)
		m0 = m1 * m0;

	printf("Mtx44RotRad: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Rotation Matrix in degrees
	//--------------------------------------------------------------------------
	n = (rand() % 16) + 15;
	m0 = Mtx44Identity();
	m1 = Mtx44RotDeg(e3_3D, 360.0f / n);

	for (long i = 0; i < n; i++)
		m0 = m1 * m0;

	printf("Mtx44RotDeg: \t\t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Transpose Matrix
	//--------------------------------------------------------------------------

	m0 = Mtx44RotRad(e3_3D, rand() / (float)(RAND_MAX) * 2.0f * PI);
	m1 = Mtx44Transpose(m0);
	m0 = m1 * m0;

	printf("Mtx44Transpose: \t%s\n",
		(CompareMtx(id, m0) < EPSILON) ? "Pass" : "Fail");

	// Vector Multiplication Matrix
	//--------------------------------------------------------------------------
	// generate 3 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	z = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	n = (rand() % 16) + 15;
	u.x = x;
	u.y = y;
	u.z = z;
	m0 = Mtx44RotRad(e3_3D, 2.0f * PI / n);

	for (long i = 0; i < n; i++)
		u = m0 * u;

	printf("Mtx44MultVec 1: \t%s\n",
		((fabsf(u.x - x) + fabsf(u.y - y)) < EPSILON) ? "Pass" : "Fail");

	// generate 3 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	z = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	n = (rand() % 16) + 15;
	u.x = x;
	u.y = y;
	u.z = z;
	m0 = Mtx44Translate(x, y, z);

	for (long i = 1; i < n; i++)
		u = m0 * u;

	printf("Mtx44MultVec 2: \t%s\n",
		((fabsf(u.x - x * n) + fabsf(u.y - y * n)) < EPSILON) ? "Pass" : "Fail");

	// Inverse Matrix
	//--------------------------------------------------------------------------
	Mtx44 mInv;
	float det = 0.0f;
	bool quit = false;

	// loop until we find an invertible matrix
	// !quit <- actual condition
	while (!true)
	{
		x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
		y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
		z = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
		m0 = Mtx44Translate(x, y, z);

		n = (rand() % 16) + 15;
		m1 = Mtx44RotRad(e3_3D, 2.0f * PI / n);

		m2 = Mtx44Scale(x, y, z);

		m3 = m0 * m1 * m2;

		Mtx44Inverse(&mInv, &det, m3);

		if (det <= EPSILON)
			continue;

		Mtx44Inverse(&mInv, &det, mInv);

		if (det <= EPSILON)
			continue;

		printf("Mtx44Inverse: \t\t%s\n",
			(CompareMtx(mInv, m3) < EPSILON) ? "Pass" : "Fail");
		quit = true;
	}
	#endif
	return 1;
}

#endif

#include "PxPhysicsAPI.h" // the beeeg include file containing all other physx includes
// #include <cstdio>
using namespace physx;
PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;
PxFoundation* gFoundation = nullptr;
PxPhysics* gPhysics = nullptr;
PxDefaultCpuDispatcher* gDispatcher = nullptr;
PxScene* gScene = nullptr;
PxMaterial* gMaterial = nullptr;
PxPvd* gPvd = nullptr;
PxReal 					stackZ = 10.0f;


void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent)
{
	PxShape* shape = gPhysics->createShape(PxBoxGeometry(halfExtent, halfExtent, halfExtent), *gMaterial);
	for (PxU32 i = 0; i < size; i++)
	{
		for (PxU32 j = 0; j < size - i; j++)
		{
			PxTransform localTm(PxVec3(PxReal(j * 2) - PxReal(size - i), PxReal(i * 2 + 1), 0) * halfExtent);
			PxRigidDynamic* body = gPhysics->createRigidDynamic(t.transform(localTm));
			body->attachShape(*shape);
			PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
			gScene->addActor(*body);
		}
	}
	shape->release();
}


//
int main()
{
	#if OLD
	float input[] =
	{
		4, 5, 8,
		3, 8, 9,
		4, 6, 6
	};

	//float input2[9] = { 0 };

	//float input4[] =
	//{
	//	4, 5, 8, 1,
	//	3, 8, 9, 1,
	//	4, 6, 6, 1,
	//	0, 0, 0, 1
	//};

	const Matrix3x3 source{ input };
	Matrix3x3 inv;
	float det;
	PrintMatrix("source", source);
	printf("det %f\n", static_cast<double>(source.Determinant()));
	PrintMatrix("inverse", Mtx33Inverse(&inv, &det, source));

	inv = Mtx33Proj(e1_2D);
	inv = Mtx33Shear(e1_2D);
	PrintMatrix("", inv);

	Test2D();
	Test3D();
	return 0;
	#endif

	printf("Hello PhysX!");
	// init physx
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	printf("%d\n", PX_PHYSICS_VERSION);
	printf("%d\n", PX_PHYSICS_VERSION_MAJOR);
	printf("%d\n", PX_PHYSICS_VERSION_MINOR);
	printf("%d\n", PX_PHYSICS_VERSION_BUGFIX);

	// init simulation
	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
	gScene->addActor(*groundPlane);

	for (PxU32 i = 0; i < 5; i++)
	{
		createStack(PxTransform(PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);
	}
	// run simulation
	while (true)
	{
		gScene->simulate(1.0f / 60.0f);
		gScene->fetchResults(true);
		//THIS FINALLY WORKS YASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
		//Viewable in PVD !!!111!!!
	}

}
