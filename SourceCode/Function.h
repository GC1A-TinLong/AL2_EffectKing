#pragma once
#include <stdlib.h>
#include <Struct.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>

float RandOutput(const int& range_min, const int& range_max, float& result);
float RandScaleOutput(const float& range_min, const float& range_max, float& result);
int iRandOutput(const int& range_min, const int& range_max, int& result);
void VoidRand(const int& range_min, const int& range_max, int& result);
void Normalization(Vector2& vector, Vector2& emitter, float &distance);
void DrawInstruction(Effect &effect);

Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);