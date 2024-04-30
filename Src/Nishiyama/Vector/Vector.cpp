#include <math.h>
#include "../Shapes/Shapes.h"
#include "Vector.h"

VECTOR CreateVec(VECTOR vec1, VECTOR vec2)
{
	VECTOR result = { 0.0f };
	result.x = vec2.x - vec1.x;
	result.y = vec2.y - vec1.y;
	result.z = vec2.z - vec1.z;

	return result;
}

float GetVecLen(VECTOR vec)
{
	return (float)sqrt((double)vec.x * (double)vec.x + (double)vec.y * (double)vec.y + (double)vec.z * (double)vec.z);
}

VECTOR NormalizeVec(VECTOR vec)
{
	VECTOR result = { 0.0f };
	float len = GetVecLen(vec);

	result.x = (vec.x / len);
	result.y = (vec.y / len);
	result.z = (vec.z / len);

	return result;
}

float VecDot(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

float VecCross2D(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

VECTOR VecCross3D(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
}

VECTOR GetVector(Object object1 , Object object2, float AbsoluteSpeed)
{
	VECTOR result = { 0.0f };
	float xv = object2.Get_pos().x - object1.Get_pos().x;
	float yv = object2.Get_pos().y - object1.Get_pos().y;
	float zv = object2.Get_pos().z - object1.Get_pos().z;
	float v = (float)sqrt((double)xv * (double)xv + (double)yv * (double)yv + (double)zv * (double)zv);

	result.x = (xv / v) * AbsoluteSpeed;
	result.y = (yv / v) * AbsoluteSpeed;
	result.z = (zv / v) * AbsoluteSpeed;

	return result;
}

VECTOR AddVec(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.x + vec2.x, vec1.y + vec2.y, vec1.y + vec2.y);
}

VECTOR SubVec(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.x - vec2.x, vec1.y - vec2.y, vec1.y - vec2.y);
}

VECTOR MulVec(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.x * vec2.x, vec1.y * vec2.y, vec1.y * vec2.y);
}

VECTOR DivVec(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.x / vec2.x, vec1.y / vec2.y, vec1.y / vec2.y);
}

VECTOR MulVec_f(VECTOR vec1, float multiplyFloat)
{
	return VGet(vec1.x * multiplyFloat, vec1.y * multiplyFloat, vec1.y * multiplyFloat);
}

VECTOR DivVec_f(VECTOR vec1, float dividedFloat)
{
	return VGet(vec1.x / dividedFloat, vec1.y / dividedFloat, vec1.y / dividedFloat);
}