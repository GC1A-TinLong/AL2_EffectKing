#include <Function.h>

float RandOutput(const int& range_min, const int& range_max, float& result) {
	return result = ((float)rand() / RAND_MAX) * (range_max + 1 - range_min) + range_min;
}
float RandScaleOutput(const float& range_min, const float& range_max, float& result) {
	return result = ((float)rand() / RAND_MAX) * (range_max + 1 - range_min) + range_min;
}
int iRandOutput(const int& range_min, const int& range_max, int& result) {
	return result = int(((float)rand() / RAND_MAX) * (range_max + 1 - range_min) + range_min);
}
void VoidRand(const int& range_min, const int& range_max, int& result) {
	result = int(((float)rand() / RAND_MAX) * (range_max + 1 - range_min) + range_min);
}
void Normalization(Vector2& vector, Vector2& emitter, float &distance) {
	distance = sqrtf(powf(vector.x - emitter.x, 2.0f) + powf(vector.y - emitter.y, 2.0f));
	vector.x -= emitter.x;
	vector.y -= emitter.y;
	if (distance != 0) {
		vector.x /= distance;
		vector.y /= distance;
	}
}

void DrawInstruction(Effect& effect)
{
	Novice::DrawBox(960, 20, 60 * 5, 40 * 6, 0, 0x303030FF, kFillModeSolid);
	Novice::DrawBox(960, 20, 60 * 5, 40 * 6, 0, 0xFFD700FF, kFillModeWireFrame);
	for (int i = 1; i < 6; i++) {
		Novice::DrawLine(960, i * 40 + 20, 960 + 60 * 6, i * 40 + 20, WHITE);
	}
	int redBoxY = 0;
	if (effect == None) {
		redBoxY = 20;
	}
	else if (effect == Bloom) {
		redBoxY = 20 + 40 * 1;
	}
	else if (effect == Charge || effect == Wave) {
		redBoxY = 20 + 40 * 2;
	}
	else if (effect == ChargeShot) {
		redBoxY = 20 + 40 * 3;
	}
	else if (effect == Spark) {
		redBoxY = 20 + 40 * 4;
	}
	
	Novice::DrawBox(960, redBoxY, 60 * 5 - 1, 40 - 1, 0, 0xe3242bff, kFillModeSolid);
	Novice::ScreenPrintf(970, 30, "R: Initialize");
	Novice::ScreenPrintf(970, 30 + (40 * 1), "1: Bloom");
	Novice::ScreenPrintf(970, 30 + (40 * 2), "SPACE: Charge");
	Novice::ScreenPrintf(970, 30 + (40 * 3), "Left Click: ChargeShot");
	Novice::ScreenPrintf(970, 30 + (40 * 4), "Right Click: Spark");
	Novice::ScreenPrintf(970, 30 + (40 * 5), "WASD/ARROW KEYS: Move");
}

Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
	Vector2 result{};
	result.x = (t * a.x + (1.0f - t) * b.x);
	result.y = (t * a.y + (1.0f - t) * b.y);
	return result;
}
Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
	Vector2 result{};
	Vector2 p0p1{};
	Vector2 p1p2{};
	p0p1 = Lerp(p0, p1, t);
	p1p2 = Lerp(p1, p2, t);
	return result = Lerp(p0p1, p1p2, t);
}
