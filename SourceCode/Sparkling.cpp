#include "Sparkling.h"

Sparkling::Sparkling() {
	emitter = { 0,0 };
	vector = { 0,0 };
	pos = { -1000,0 };
	randSpawnPos1 = { 0,0 };
	randSpawnPos2 = { 0,0 };
	randSpawnPos3 = { 0,0 };
	radius = 10;

	t = 0;
	endframe = 45.0f;
	randP1 = { 0,0 };
	randP2 = { 0,0 };
	randP3 = { 0,0 };
	randArea2 = 0;
	randArea3 = 0;

	start = 0;

	endTimer = 0;
	resetTimer = 0;

	color = WHITE;
	randColor = 0;
	R = 0;
	G = 0;
	B = 0;
	A = 255;
	randRadius = 0;
}
void Sparkling::Initialization() {
	emitter = { 0,0 };
	vector = { 0,0 };
	pos = { -1000,0 };
	randSpawnPos1 = { 0,0 };
	randSpawnPos2 = { 0,0 };
	randSpawnPos3 = { 0,0 };
	radius = 10;

	t = 0;
	endframe = 45.0f;
	randP1 = { 0,0 };
	randP2 = { 0,0 };
	randP3 = { 0,0 };
	randArea2 = 0;
	randArea3 = 0;

	start = 0;

	endTimer = 0;
	resetTimer = 0;

	color = WHITE;
	randColor = 0;
	R = 0;
	G = 0;
	B = 0;
	A = 255;
	randRadius = 0;
}

void Sparkling::SparkSpawn(Vector2i& mouse)
{
	const int kRandNum2 = 150;
	const int kAdjustNum2 = 20;
	const int kRandNum3 = 150;
	const int kAdjustNum3 = 20;

	if (start == 0) {
		pos.x = (float)mouse.x;
		pos.y = (float)mouse.y;
#pragma region Rand Spawn Pos
		randP1.x = pos.x + RandOutput(-10, 10, randSpawnPos1.x);
		randP1.y = pos.y + RandOutput(-10, 10, randSpawnPos1.y);
		VoidRand(0, 3, randArea2);
		switch (randArea2) {
		case Top:
			randP2.x = pos.x + RandOutput(-kRandNum2, kRandNum2, randSpawnPos2.x);
			randP2.y = pos.y - kRandNum2 + RandOutput(0, kAdjustNum2, randSpawnPos2.y);
			break;

		case Bottom:
			randP2.x = pos.x + RandOutput(-kRandNum2, kRandNum2, randSpawnPos2.x);
			randP2.y = pos.y + kRandNum2 + RandOutput(0, kAdjustNum2, randSpawnPos2.y);
			break;

		case Left:
			randP2.x = pos.x - kRandNum2 + RandOutput(0, kAdjustNum2, randSpawnPos2.x);
			randP2.y = pos.y + RandOutput(-kRandNum2, kRandNum2, randSpawnPos2.y);
			break;

		case Right:
			randP2.x = pos.x + kRandNum2 + RandOutput(0, kAdjustNum2, randSpawnPos2.x);
			randP2.y = pos.y + RandOutput(-kRandNum2, kRandNum2, randSpawnPos2.y);
			break;
		}
		VoidRand(0, 3, randArea3);
		switch (randArea3) {
		case Top:
			randP3.x = pos.x + RandOutput(-kRandNum3, kRandNum3, randSpawnPos2.x);
			randP3.y = pos.y - kRandNum3 + RandOutput(0, kAdjustNum3, randSpawnPos2.y);
			break;

		case Bottom:
			randP3.x = pos.x + RandOutput(-kRandNum3, kRandNum3, randSpawnPos2.x);
			randP3.y = pos.y + kRandNum3 + RandOutput(0, kAdjustNum3, randSpawnPos2.y);
			break;

		case Left:
			randP3.x = pos.x - kRandNum3 + RandOutput(0, kAdjustNum3, randSpawnPos2.x);
			randP3.y = pos.y + RandOutput(-kRandNum3, kRandNum3, randSpawnPos2.y);
			break;

		case Right:
			randP3.x = pos.x + kRandNum3 + RandOutput(0, kAdjustNum3, randSpawnPos2.x);
			randP3.y = pos.y + RandOutput(-kRandNum3, kRandNum3, randSpawnPos2.y);
			break;
		}
#pragma endregion
		randColor = rand() % 2;
		A = 0x000000FF;
		if (randColor == 0) {
			R = 0xFF;
			G = 0xFF;
			B = 0xFF;
			R <<= 24;
			G <<= 16;
			B <<= 8;
		}
		else {
			R = 0x00;
			G = 0x00;
			B = 0x00;
			R <<= 24;
			G <<= 16;
			B <<= 8;
		}
		VoidRand(3, 8, randRadius);

		start = 1;
	}
}
void Sparkling::SparkEffect() {
	if (start == 1) {
		if (A >= 8) {
			A -= 7;
		}
		if (A <= 8) {
			pos.x = -1000;
		}
		color = R + G + B + A;
		pos = Bezier(randP3, randP2, randP1, t);
		if (t != 1.0f) {
			t += 1 / endframe;
		}
		if (t >= 1.0f) {
			t = 1.0f;
			pos.x = -1000;
			//start = 0;
		}
	}
}

void Sparkling::Draw() {
	if (start == 1) {
		Novice::DrawEllipse(int(pos.x), int(pos.y), randRadius, randRadius, 0, color, kFillModeSolid);
	}
}
