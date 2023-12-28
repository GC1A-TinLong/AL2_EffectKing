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
	Novice::DrawBox(950, 20, 60 * 5, 40 * 5, 0, 0x999999FF, kFillModeSolid);
	Novice::DrawBox(950, 20, 60 * 5, 40 * 5, 0, WHITE, kFillModeWireFrame);
	for (int i = 0; i < 5; i++) {
		Novice::DrawLine(950, i * 40 + 20, 950 + 60 * 5, i * 40 + 20, WHITE);
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
	/*if (effect == Multiply) {
		redBoxY = 20 + 40 * 4;
	}
	if (effect == Screen) {
		redBoxY = 20 + 40 * 5;
	}*/
	Novice::DrawBox(950, redBoxY, 60 * 5 - 1, 40 - 1, 0, 0xe3242bff, kFillModeSolid);
	Novice::ScreenPrintf(960, 30, "R: Initialize");
	Novice::ScreenPrintf(960, 30 + (40 * 1), "1: Bloom");
	Novice::ScreenPrintf(960, 30 + (40 * 2), "SPACE: Charge");
	Novice::ScreenPrintf(960, 30 + (40 * 3), "Left Click: ChargeShot");
	Novice::ScreenPrintf(960, 30 + (40 * 4), "WASD: Move");
}
