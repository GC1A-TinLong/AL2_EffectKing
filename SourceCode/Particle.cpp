#include "Particle.h"

Particle::Particle() {
	emitter_.x = -1000;
	emitter_.y = 0;
	vector_.x = 0;
	vector_.y = 0;
	pos_.x = -1000;
	pos_.y = 0;
	randSpawnPos_.x = 0;
	randSpawnPos_.y = 0;
	halfsize_.w = 40;
	halfsize_.h = 40;
	spd_ = 1.0f;

	randArea = 0;
	randRadius = 0;

	effectStart_ = 0;
	spawnStart_ = 0;
	bufStart_ = 0;
	bloomStart_ = 0;

	distanceFromEmitter_ = 0;
	normalizedSpd_ = 0;
	endTimer_ = 180;
	resetTimer_ = 0;

	srand(unsigned int(time(nullptr)));
	R = rand() % 255;
	G = rand() % 255;
	B = rand() % 255;
	R <<= 24;
	G <<= 16;
	B <<= 8;
	A = 0x000000FF;
	color_ = R + G + B + A;

	theta = 0;
	amplitude = 50.0f;
	waveSpd = 6.0f;
	randWaveDirection = 0;
	wavePos = { 0,0 };
	tempPos = { 0,0 };
}
void Particle::Initialization() {
	emitter_.x = -1000;
	emitter_.y = 0;
	vector_.x = 0;
	vector_.y = 0;
	pos_.x = -1000;
	pos_.y = 0;
	randSpawnPos_.x = 0;
	randSpawnPos_.y = 0;
	halfsize_.w = 40;
	halfsize_.h = 40;
	spd_ = 1.0f;

	effectStart_ = 0;
	spawnStart_ = 0;
	bufStart_ = 0;
	distanceFromEmitter_ = 0;
	normalizedSpd_ = 0;
	endTimer_ = 180;
	resetTimer_ = 0;

	R = rand() % 255;
	G = rand() % 255;
	B = rand() % 255;
	R <<= 24;
	G <<= 16;
	B <<= 8;
	A = 0x000000FF;
	color_ = R + G + B + A;
	randRadius = 0;

	theta = 0;
	amplitude = 30.0f;
	waveSpd = 5.5f;
	randWaveDirection = 0;
	wavePos = { 0,0 };
	tempPos = { 0,0 };
}
Particle::~Particle() {}

void Particle::Normalization(Vector2& vector, Vector2& emitter) {
	distanceFromEmitter_ = sqrtf(powf(vector.x - emitter.x, 2.0f) + powf(vector.y - emitter.y, 2.0f));
	vector.x -= emitter.x;
	vector.y -= emitter.y;
	if (distanceFromEmitter_ != 0) {
		vector.x /= distanceFromEmitter_;
		vector.y /= distanceFromEmitter_;
	}
}
void Particle::Normalization_toEmitter(Vector2& vector, Vector2& emitter) {
	distanceFromEmitter_ = sqrtf(powf(emitter.x - vector.x, 2.0f) + powf(emitter.y - vector.y, 2.0f));
	vector.x = emitter.x - vector.x;
	vector.y = emitter.y - vector.y;
	if (distanceFromEmitter_ != 0) {
		vector.x /= distanceFromEmitter_;
		vector.y /= distanceFromEmitter_;
	}
}

void Particle::Blooming(Vector2& pos) {
	if (resetTimer_ == 0 && bloomStart_ == 1) {
		emitter_.x = (float)pos.x;
		emitter_.y = (float)pos.y;
		pos_.x = emitter_.x + RandOutput(-10, 10, randSpawnPos_.x);
		pos_.y = emitter_.y + RandOutput(-10, 10, randSpawnPos_.y);

		vector_.x = RandOutput(-50, 50, vector_.x) + emitter_.x;
		vector_.y = RandOutput(-50, 50, vector_.y) + emitter_.y;
		Normalization(vector_, emitter_);

		VoidRand(5, 18, randRadius);

		randColor = rand() % 2;
		if (randColor == 0) {
			R = 0xFF;
			G = 0xFF;
			B = 0xFF;
			R <<= 24;
			G <<= 16;
			B <<= 8;
		}
		else {
			R = 0x35;
			G = 0x35;
			B = 0x35;
			R <<= 24;
			G <<= 16;
			B <<= 8;
		}
	}
	if (effectStart_ == 1) {
		pos_.x += vector_.x * spd_;
		pos_.y += vector_.y * spd_;
		resetTimer_++;
		color_ = R + G + B + A;
		A -= 3;
	}
	if (A <= 1) {
		A = 0x000000FF;
		effectStart_ = 0;
		resetTimer_ = 0;
		pos_.x = emitter_.x;
		pos_.y = emitter_.y;
	}
	if (resetTimer_ >= endTimer_) {
		effectStart_ = 0;
		A = 0x000000FF;
		resetTimer_ = 0;
		pos_.x = emitter_.x;
		pos_.y = emitter_.y;
	}
}

void Particle::Charging(Vector2& pos)
{
	emitter_.x = pos.x;
	emitter_.y = pos.y;
	vector_.x = pos_.x;
	vector_.y = pos_.y;
	Normalization_toEmitter(vector_, emitter_);
	if (effectStart_ == 1) {
		pos_.x += vector_.x * spd_;
		pos_.y += vector_.y * spd_;
		if (A < 0x000000FE) {
			A += 10;
		}
		color_ = R + G + B + A;
		if (A >= 0x000000FF - 10) {
			A = 0x000000FF;
		}
	}
	if (fabsf(pos_.x - emitter_.x) <= spd_ && fabsf(pos_.y - emitter_.y) <= spd_) {
		effectStart_ = 0;
	}
}
void Particle::MouseCharging(Vector2& pos)
{
	emitter_.x = pos.x;
	emitter_.y = pos.y;
	vector_.x = pos_.x;
	vector_.y = pos_.y;
	Normalization_toEmitter(vector_, emitter_);
	if (effectStart_ == 1) {
		pos_.x += vector_.x * spd_;
		pos_.y += vector_.y * spd_;
		if (A < 0x000000FE) {
			A += 3;
		}
		color_ = R + G + B + A;
		if (A >= 0x000000FF - 3) {
			A = 0x000000FF;
		}
	}
	if (fabsf(pos_.x - emitter_.x) <= spd_ && fabsf(pos_.y - emitter_.y) <= spd_) {
		pos_.x = -1000;
	}
}

void Particle::Spawning(Vector2& pos, Effect& effect)
{
	const int kRandNum = 100;
	const int kAdjustNum = 20;

	if (effect == Charge) {
		VoidRand(5, 18, randRadius);
	}
	else if (effect == ChargeShot) {
		VoidRand(5, 13, randRadius);
	}

	if (spawnStart_ == 1) {
		emitter_.x = pos.x;
		emitter_.y = pos.y;
		VoidRand(0, 3, randArea);
		switch (randArea) {
		case Top:
			pos_.x = emitter_.x + RandOutput(-kRandNum, kRandNum, randSpawnPos_.x);
			pos_.y = emitter_.y - 100 + RandOutput(0, kAdjustNum, randSpawnPos_.y);
			break;

		case Bottom:
			pos_.x = emitter_.x + RandOutput(-kRandNum, kRandNum, randSpawnPos_.x);
			pos_.y = emitter_.y + 100 - RandOutput(0, kAdjustNum, randSpawnPos_.y);
			break;

		case Left:
			pos_.x = emitter_.x - 100 + RandOutput(0, kAdjustNum, randSpawnPos_.x);
			pos_.y = emitter_.y + RandOutput(-kRandNum, kRandNum, randSpawnPos_.y);
			break;

		case Right:
			pos_.x = emitter_.x + 100 - RandOutput(0, kAdjustNum, randSpawnPos_.x);
			pos_.y = emitter_.y + RandOutput(-kRandNum, kRandNum, randSpawnPos_.y);
			break;
		}


		randColor = rand() % 2;
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
		
		A = 0x00000055;
		color_ = R + G + B + A;
		//color_ =WHITE;

		effectStart_ = 1;
	}
}

void Particle::SpawnOfWave(Player& player)
{
	if (resetTimer_ == 0) {
		emitter_.x = player.pos_.x;
		emitter_.y = player.pos_.y;
		randSpawnPos_.x = RandOutput(-40, 40, randSpawnPos_.x);
		pos_.x = emitter_.x + randSpawnPos_.x;
		pos_.y = emitter_.y + RandOutput(-30, 20, randSpawnPos_.y) + 20.0f;

		VoidRand(5, 18, randRadius);
		VoidRand(0, 1, randWaveDirection);

		randColor = rand() % 2;
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

		A = 0x000000FF;
		color_ = R + G + B + A;
		//color_ = WHITE;

		effectStart_ = 1;
	}
}

void Particle::Waving(Player& player)
{
	if (effectStart_ == 1) {
		resetTimer_++;
		if (resetTimer_ == 1) {
			tempPos = player.pos_;
		}

		if (randWaveDirection == 0) {
			wavePos.x = -(sinf(theta) * amplitude);
		}
		else if (randWaveDirection == 1) {
			wavePos.x = (sinf(theta) * amplitude);
		}
		theta += float(M_PI) / 20.0f;
		pos_.x = tempPos.x + wavePos.x + randSpawnPos_.x;
		pos_.y -= waveSpd;

		A -= 4;
		color_ = R + G + B + A;
	}
	if (A < 5) {
		effectStart_ = 0;
		resetTimer_ = 0;
		A = 0x000000FF;
	}
}


void Particle::Draw(/*int handle, Mode mode*/) {
	if (effectStart_ == 1) {
		Novice::DrawEllipse(int(pos_.x), int(pos_.y), randRadius, randRadius, 0, color_, kFillModeSolid);
	}
	/*switch (mode) {
	case None:
		Novice::SetBlendMode(BlendMode::kBlendModeNone);
		Novice::DrawSprite(int(pos_.x) - int(halfsize_.w * scale), (int)pos_.y - int(halfsize_.h * scale), handle, scale, scale, 0, color_);
		break;

	case Normal:
		Novice::SetBlendMode(BlendMode::kBlendModeNormal);
		Novice::DrawSprite(int(pos_.x) - int(halfsize_.w * scale), (int)pos_.y - int(halfsize_.h * scale), handle, scale, scale, 0, color_);
		break;

	case Add:
		Novice::SetBlendMode(BlendMode::kBlendModeAdd);
		Novice::DrawSprite(int(pos_.x) - int(halfsize_.w * scale), (int)pos_.y - int(halfsize_.h * scale), handle, scale, scale, 0, color_);
		break;

	case Subtract:
		Novice::SetBlendMode(BlendMode::kBlendModeSubtract);
		Novice::DrawSprite(int(pos_.x) - int(halfsize_.w * scale), (int)pos_.y - int(halfsize_.h * scale), handle, scale, scale, 0, color_);
		break;

	case Multiply:
		Novice::SetBlendMode(BlendMode::kBlendModeMultily);
		Novice::DrawSprite(int(pos_.x) - int(halfsize_.w * scale), (int)pos_.y - int(halfsize_.h * scale), handle, scale, scale, 0, color_);
		break;

	case Screen:
		Novice::SetBlendMode(BlendMode::kBlendModeScreen);
		Novice::DrawSprite(int(pos_.x) - int(halfsize_.w * scale), (int)pos_.y - int(halfsize_.h * scale), handle, scale, scale, 0, color_);
		break;
	}*/
}

void ModeSelect(char* keys, char* preKeys, Mode& mode)
{
	if (keys[DIK_1] && !preKeys[DIK_1]) {
		mode = NoBlend;
	}
	if (keys[DIK_2] && !preKeys[DIK_2]) {
		mode = Normal;
	}
	if (keys[DIK_3] && !preKeys[DIK_3]) {
		mode = Add;
	}
	if (keys[DIK_4] && !preKeys[DIK_4]) {
		mode = Subtract;
	}
	if (keys[DIK_5] && !preKeys[DIK_5]) {
		mode = Multiply;
	}
	if (keys[DIK_6] && !preKeys[DIK_6]) {
		mode = Screen;
	}
}

