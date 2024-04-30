#pragma once

VECTOR CreateVec(VECTOR vec1, VECTOR vec2);

float GetVecLen(VECTOR vec);

VECTOR NormalizeVec(VECTOR vec);

float VecDot(VECTOR vec1, VECTOR vec2);

float VecCross2D(VECTOR vec1, VECTOR vec2);

VECTOR VecCross3D(VECTOR vec1, VECTOR vec2);

VECTOR GetVector(Object object1, Object object2, float AbsoluteSpeed);

VECTOR AddVec(VECTOR vec1, VECTOR vec2);

VECTOR SubVec(VECTOR vec1, VECTOR vec2);

VECTOR MulVec(VECTOR vec1, VECTOR vec2);

VECTOR DivVec(VECTOR vec1, VECTOR vec2);

VECTOR MulVec_f(VECTOR vec1, float multiplyFloat);

VECTOR DivVec_f(VECTOR vec1, float dividedFloat);
