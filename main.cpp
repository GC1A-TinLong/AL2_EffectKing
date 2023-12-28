#include <Novice.h>
#include <Player.h>
#include <Particle.h>

const char kWindowTitle[] = "GC1A_10_チョウ_テンロウ";

const int kParticleNum = 200;
const int kChargeNum = 60;

void ScreenShake_Amplitude(Vector2& amplitude) {
	const int kRand = 20;
	amplitude.x = RandOutput(-kRand, kRand, amplitude.x);
	amplitude.y = RandOutput(-kRand, kRand, amplitude.y);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Effect effect = None;
	Effect preEffect = None;

	Player* player = new Player;

	Particle* particle[kParticleNum]{};
	for (int i = 0; i < kParticleNum; i++) {
		particle[i] = new Particle;
		particle[i]->Initialization();
	}

	int chargeStart = 0;
	int waveStartTimer = 0;
	int chargeShakeEndTimer = 0;
	int chargeEndTimer = 0;

	int		chargeShake = 0;
	float	chargeShakeAmplitude = 41.0f;
	float	shrinkrate = chargeShakeAmplitude * 0.045f;
	Vector2 randDistance{};

	Vector2i mouse{};
	int chargeShotStart = 0;
	int isPressingMouse = 0;
	int isShot = 0;
	int isHitWall = 0;

	int chargeGaugeTop = 0;
	int chargeGaugeBot = 0;
	int gaugeTimer = 0;
	int endGaugeTimer = 135;
	int isGaugeFilling = 0;
	unsigned int gaugeColor = RED;
	int R = 0;
	int G = 0;
	int B = 0;
	int A = 255;


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (chargeStart == 0 && isGaugeFilling == 0) {
			player->Control(keys);
		}
#pragma region DIK_R Initialization
		if (keys[DIK_R] && !preKeys[DIK_R]) {
			player->Initialization();
			for (int i = 0; i < kParticleNum; i++) {
				particle[i]->Initialization();
			}
			player->bullet->Initialization();
			effect = None;
			preEffect = None;

			chargeStart = 0;
			waveStartTimer = 0;
			chargeShakeEndTimer = 0;
			chargeEndTimer = 0;
			chargeShake = 0;
			chargeShakeAmplitude = 41.0f;
			shrinkrate = chargeShakeAmplitude * 0.045f;
			randDistance = { 0,0, };
			chargeShotStart = 0;
			isPressingMouse = 0;
			isHitWall = 0;
			isShot = 0;
			chargeGaugeTop = 0;
			chargeGaugeBot = 0;
			gaugeTimer = 0;
			endGaugeTimer = 135;
			isGaugeFilling = 0;
			gaugeColor = RED;
			R = 0;
			G = 0;
			B = 0;
			A = 255;
		}
#pragma endregion

		switch (effect) {
		case None:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				effect = Charge;
				preEffect = None;
				chargeStart = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
			}
			if (keys[DIK_1] && !preKeys[DIK_1]) {
				effect = Bloom;
				preEffect = None;
				chargeStart = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
			}

			if (Novice::IsTriggerMouse(0)) {
				effect = ChargeShot;
				chargeShotStart = 0;
				chargeStart = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
			}

			break;
#pragma region CASE Charge
		case Charge:
			chargeStart = 1;
			if (preEffect != Charge) {
				for (int i = 0; i < kChargeNum; i++) {
					particle[i]->spd_ = 2.5f;
					particle[i]->bufStart_ = 1;
				}
			}
			preEffect = Charge;

			for (int i = 0; i < kChargeNum; i++) {
				if (chargeStart == 1 && particle[i]->effectStart_ == 0) {
					particle[i]->spawnStart_ = 1;

					particle[i]->Spawning(player->pos_);

					if (i % 4 == 0) {
						break;
					}
				}
			}
			for (int i = 0; i < kChargeNum; i++) {
				if (particle[i]->spawnStart_ == 1) {
					particle[i]->spawnStart_ = 0;
				}
				particle[i]->Charging(player->pos_);
			}
			if (chargeEndTimer != 120) {
				chargeEndTimer++;
			}

			if (chargeEndTimer == 120) {
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->A = 0x000000FF;
				}
			}
			if (chargeEndTimer >= 120) {
				if (chargeShakeAmplitude >= 1) {
					randDistance.x = rand() % (int)chargeShakeAmplitude - chargeShakeAmplitude / 2.0f;
					randDistance.y = rand() % (int)chargeShakeAmplitude - chargeShakeAmplitude / 2.0f;
				}
				if (chargeShakeEndTimer >= 0 && chargeShakeEndTimer < chargeShakeEndTimer * 0.2f) {
					chargeShakeAmplitude -= shrinkrate;
				}
				else if (chargeShakeEndTimer >= chargeShakeEndTimer * 0.2f && chargeShakeEndTimer < chargeShakeEndTimer * 0.6f) {
					chargeShakeAmplitude -= shrinkrate * 0.75f;
				}
				else if (chargeShakeEndTimer >= chargeShakeEndTimer * 0.6f) {
					chargeShakeAmplitude -= shrinkrate * 0.25f;
				}
				chargeShake = 1;
				chargeShakeEndTimer++;
				for (int i = 0; i < kParticleNum; i++) {
					if (particle[i]->A >= 2) {
						particle[i]->A -= 2;
					}
					if (particle[i]->A <= 3) {
						particle[i]->A = 0x00000001;
					}
					particle[i]->pos_.x = -1000;
				}
			}
			if (chargeShakeEndTimer >= 90) {
				chargeShake = 0;
				chargeEndTimer = 0;
				chargeShakeEndTimer = 0;
				waveStartTimer = 0;
				chargeShakeAmplitude = 41.0f;
				shrinkrate = chargeShakeAmplitude * 0.045f;

				chargeStart = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->effectStart_ = 0;
					particle[i]->resetTimer_ = 0;
				}

				effect = Wave;
			}
			if (Novice::IsTriggerMouse(0)) {
				chargeShotStart = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
				isShot = 0;
				player->bullet->Initialization();
				chargeStart = 0;
				chargeEndTimer = 0;
				chargeShake = 0;
				chargeShakeAmplitude = 41.0f;
				shrinkrate = chargeShakeAmplitude * 0.045f;
				effect = ChargeShot;
			}

			if (keys[DIK_1] && !preKeys[DIK_1]) {
				chargeShotStart = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->effectStart_ = 0;
				}
				player->bullet->Initialization();
				chargeStart = 0;
				chargeEndTimer = 0;
				chargeShake = 0;
				chargeShakeAmplitude = 41.0f;
				shrinkrate = chargeShakeAmplitude * 0.045f;

				effect = Bloom;
			}

			break;
#pragma endregion
#pragma region CASE Wave
		case Wave:
			preEffect = Wave;
			for (int i = 0; i < kParticleNum; i++) {
				if (particle[i]->resetTimer_ == 0) {
					particle[i]->SpawnOfWave(*player);
					if (i % 3 == 0) {
						break;
					}
				}
			}
			for (int i = 0; i < kParticleNum; i++) {
				particle[i]->Waving(*player);
			}

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				effect = Charge;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->effectStart_ = 0;
					particle[i]->pos_.x = -1000;
				}
				player->bullet->Initialization();
				/*for (int i = 0; i < kChargeNum; i++) {
					particle[i]->spd_ = 2.5f;
					particle[i]->bufStart_ = 1;
				}*/
			}

			if (Novice::IsTriggerMouse(0)) {
				chargeShotStart = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
				player->bullet->Initialization();
				isShot = 0;
				chargeStart = 0;
				chargeEndTimer = 0;
				chargeShake = 0;
				chargeShakeAmplitude = 41.0f;
				shrinkrate = chargeShakeAmplitude * 0.045f;
				chargeShakeEndTimer = 0;
				isHitWall = 0;

				effect = ChargeShot;
			}
			if (keys[DIK_1] && !preKeys[DIK_1]) {
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
				player->bullet->Initialization();
				chargeEndTimer = 0;
				chargeShakeEndTimer = 0;
				chargeStart = 0;
				chargeShake = 0;
				chargeShakeAmplitude = 41.0f;
				shrinkrate = chargeShakeAmplitude * 0.045f;

				effect = Bloom;
				preEffect = None;
			}

			break;
#pragma endregion
#pragma region CASE Bloom
		case Bloom:
			if (preEffect != Bloom) {
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->bufStart_ = 1;		//Effect keep going flag
					particle[i]->bloomStart_ = 1;
					particle[i]->spd_ = 1.5f;
					particle[i]->A = 255;
				}
			}
			preEffect = Bloom;

			for (int i = 0; i < kParticleNum; i++) {
				if (particle[i]->effectStart_ == 0 && particle[i]->bufStart_ == 1) {
					particle[i]->effectStart_ = 1;
					if (i % 2 == 0) {
						break;
					}
				}
			}
			for (int i = 0; i < kParticleNum; i++) {
				particle[i]->Blooming(player->pos_);
			}


			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->effectStart_ = 0;
				}
				player->bullet->Initialization();
				chargeStart = 0;
				chargeEndTimer = 0;

				effect = Charge;
			}
			if (Novice::IsTriggerMouse(0)) {
				chargeShotStart = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
				player->bullet->Initialization();
				chargeStart = 0;
				chargeEndTimer = 0;

				effect = ChargeShot;
			}

			break;
#pragma endregion
#pragma region CASE ChargeShot
		case ChargeShot:
			preEffect = ChargeShot;

			if (Novice::IsTriggerMouse(0)) {
				chargeShotStart = 0;
				isShot = 0;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
			}
			if (Novice::IsPressMouse(0)) {
				Novice::GetMousePosition(&mouse.x, &mouse.y);
				player->bullet->pos.x = player->pos_.x;
				player->bullet->pos.y = player->pos_.y;
				isPressingMouse = 1;
				isGaugeFilling = 1;

				player->bullet->color = 0xFF000088;

				for (int i = 0; i < 100; i++) {
					if (particle[i]->effectStart_ == 0) {
						particle[i]->spawnStart_ = 1;

						particle[i]->Spawning(player->pos_);

						if (i % 4 == 0) {
							break;
						}
					}
				}
				for (int i = 0; i < 100; i++) {
					if (particle[i]->spawnStart_ == 1) {
						particle[i]->spawnStart_ = 0;
					}
					particle[i]->MouseCharging(player->pos_);
				}

				if (gaugeTimer >= endGaugeTimer) {
					isShot = 1;
					chargeShotStart = 1;
					isGaugeFilling = 0;
					R = rand() % 255;
					G = rand() % 255;
					B = rand() % 255;
					R <<= 24;
					G <<= 16;
					B <<= 8;
					gaugeColor = R + G + B + A;
					player->bullet->color = 0xFF000088;

					randDistance.x = float(rand() % 21 - 10);
					randDistance.y = float(rand() % 21 - 10);

					for (int i = 0; i < 100; i++) {
						particle[i]->effectStart_ = 0;
					}
				}
				player->vector.x = (float)mouse.x;
				player->vector.y = (float)mouse.y;

				Normalization(player->vector, player->pos_, player->mouseDistance);
				player->bullet->pos.x += 1.5f * (player->vector.x * player->bullet->spd);
				player->bullet->pos.y += 1.5f * (player->vector.y * player->bullet->spd);

				gaugeTimer++;
			}
			if (gaugeTimer < endGaugeTimer) {
				//bot=p+40
				//top=p-60;
				if (chargeGaugeTop >= -(endGaugeTimer - 2)) {
					chargeGaugeTop--;
					chargeGaugeBot++;
				}
			}

			if (Novice::IsPressMouse(0) == 0) {
				isPressingMouse = 0;
				chargeGaugeTop = 0;
				chargeGaugeBot = 0;
				gaugeTimer = 0;
				isGaugeFilling = 0;

				R = 0;
				G = 0;
				B = 0;
				gaugeColor = RED;
				player->bullet->color = RED;

				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
				if (isShot == 0) {
					player->bullet->Initialization();
				}
			}
			if (chargeShotStart == 1 && isPressingMouse == 0) {
				player->ChargingShot(mouse);
			}
			if (isShot == 1) {
				if (player->bullet->pos.x >= 1280.0f - player->bullet->radius) {
					chargeShotStart = 0;
					isHitWall = 1;
					player->bullet->pos.x = 1280.0f - player->bullet->radius;
				}
				if (player->bullet->pos.x <= player->bullet->radius) {
					chargeShotStart = 0;
					isHitWall = 1;
					player->bullet->pos.x = (float)player->bullet->radius;
				}
				if (player->bullet->pos.y >= 720.0f - player->bullet->radius) {
					chargeShotStart = 0;
					isHitWall = 1;
					player->bullet->pos.y = 720.0f - player->bullet->radius;
				}
				if (player->bullet->pos.y <= player->bullet->radius) {
					chargeShotStart = 0;
					isHitWall = 1;
					player->bullet->pos.y = (float)player->bullet->radius;
				}
				/*if (chargeShotStart == 0) {
					player->bullet->Initialization();
				}*/
			}
			if (isHitWall == 1) {
				isShot = 0;
				player->bullet->Initialization();
				if (chargeEndTimer != 120) {
					chargeEndTimer++;
				}

				if (chargeEndTimer < 120) {
					if (chargeShakeAmplitude >= 1) {
						randDistance.x = rand() % (int)chargeShakeAmplitude - chargeShakeAmplitude / 2.0f;
						randDistance.y = rand() % (int)chargeShakeAmplitude - chargeShakeAmplitude / 2.0f;
					}
					if (chargeShakeEndTimer >= 0 && chargeShakeEndTimer < chargeShakeEndTimer * 0.2f) {
						chargeShakeAmplitude -= shrinkrate;
					}
					else if (chargeShakeEndTimer >= chargeShakeEndTimer * 0.2f && chargeShakeEndTimer < chargeShakeEndTimer * 0.6f) {
						chargeShakeAmplitude -= shrinkrate * 0.75f;
					}
					else if (chargeShakeEndTimer >= chargeShakeEndTimer * 0.6f) {
						chargeShakeAmplitude -= shrinkrate * 0.25f;
					}
				}
			}
			if (chargeEndTimer == 120) {
				isHitWall = 0;
				chargeEndTimer = 0;
				chargeShake = 0;
				chargeShakeAmplitude = 41.0f;
				shrinkrate = chargeShakeAmplitude * 0.045f;

			}

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
				player->bullet->Initialization();
				chargeStart = 0;
				chargeEndTimer = 0;
				chargeShake = 0;
				chargeShakeAmplitude = 41.0f;
				shrinkrate = chargeShakeAmplitude * 0.045f;

				effect = Charge;
			}
			if (keys[DIK_1] && !preKeys[DIK_1]) {
				preEffect = None;
				for (int i = 0; i < kParticleNum; i++) {
					particle[i]->Initialization();
				}
				player->bullet->Initialization();
				chargeStart = 0;
				chargeEndTimer = 0;
				chargeShake = 0;
				chargeShakeAmplitude = 41.0f;
				shrinkrate = chargeShakeAmplitude * 0.045f;

				effect = Bloom;
			}

			break;
#pragma endregion
		}




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(0, 0, 1280, 720, 0, 0x707070FF, kFillModeSolid);
		if (chargeShake == 0 && isHitWall == 0) {
			for (int i = 0; i < 30; i++) {
				Novice::DrawLine(i * 50 - 190, -100, i * 50 - 190, 900, WHITE);
			}
			for (int j = 0; j < 20; j++) {
				Novice::DrawLine(-100, j * 50 - 190, 1400, j * 50 - 190, WHITE);
			}
			DrawInstruction(effect);
		}
		

		//Particle
		if (chargeShake == 0 && isHitWall == 0) {
			for (int i = 0; i < kParticleNum; i++) {
				if (particle[i]->effectStart_ == 1) {
					particle[i]->Draw();
				}
			}
		}

		/*else if (chargeShake == 1) {
			for (int i = 0; i < kParticleNum; i++) {
				Novice::DrawEllipse(int(particle[i]->pos_.x + randDistance.x), int(particle[i]->pos_.y + randDistance.y),
					particle[i]->randRadius, particle[i]->randRadius, 0, particle[i]->color_, kFillModeSolid);
			}
		}*/
		if (effect == Bloom) {
			//BG
			for (int i = 0; i < 30; i++) {
				Novice::DrawLine(i * 50 - 190, -100, i * 50 - 190, 900, WHITE);
			}
			for (int j = 0; j < 20; j++) {
				Novice::DrawLine(-100, j * 50 - 190, 1400, j * 50 - 190, WHITE);
			}

			for (int i = 0; i < kParticleNum; i++) {
				if (particle[i]->effectStart_ == 1) {
					particle[i]->Draw();
				}
			}
			DrawInstruction(effect);
		}
		//Player
		if (effect != Charge && effect != Wave && effect != ChargeShot) {
			player->Draw();
		}
		if (effect == Charge || effect == Wave) {
			if (chargeShake == 0) {
				//BG
				for (int i = 0; i < 30; i++) {
					Novice::DrawLine(i * 50 - 190, -100, i * 50 - 190, 900, WHITE);
				}
				for (int j = 0; j < 20; j++) {
					Novice::DrawLine(-100, j * 50 - 190, 1400, j * 50 - 190, WHITE);
				}

				for (int i = 0; i < kParticleNum; i++) {
					if (particle[i]->effectStart_ == 1) {
						particle[i]->Draw();
					}
				}
				DrawInstruction(effect);
				//Player
				player->Draw();
			}
			else if (chargeShake == 1) {
				//BG
				for (int i = 0; i < 30; i++) {
					Novice::DrawLine(i * 50 - 190 + (int)randDistance.x, -100, i * 50 - 190 + (int)randDistance.x, 900, WHITE);
				}
				for (int j = 0; j < 20; j++) {
					Novice::DrawLine(-100, j * 50 - 190 + (int)randDistance.y, 1400, j * 50 - 190 + (int)randDistance.y, WHITE);
				}
				DrawInstruction(effect);
				//par
				for (int i = 0; i < kParticleNum; i++) {
					Novice::DrawEllipse(int(particle[i]->pos_.x + randDistance.x), int(particle[i]->pos_.y + randDistance.y),
						particle[i]->randRadius, particle[i]->randRadius, 0, particle[i]->color_, kFillModeSolid);
				}
				//Player
				Novice::DrawEllipse((int)player->pos_.x + (int)randDistance.x, (int)player->pos_.y + (int)randDistance.y,
					(int)player->size_.w, (int)player->size_.h, 0, player->color_, kFillModeSolid);
			}
		}
		else if (effect == ChargeShot) {
			if (isHitWall == 0) {
				DrawInstruction(effect);
				if (gaugeTimer >= endGaugeTimer) {
					for (int i = 0; i < kParticleNum; i++) {
						if (particle[i]->effectStart_ == 1) {
							particle[i]->Draw();
						}
					}
					//bullet
					Novice::DrawEllipse(int(player->bullet->pos.x) + (int)randDistance.x, int(player->bullet->pos.y) + (int)randDistance.y,
						player->bullet->radius, player->bullet->radius, 0, player->bullet->color, kFillModeSolid);
					//player
					Novice::DrawEllipse((int)player->pos_.x + (int)randDistance.x, (int)player->pos_.y + (int)randDistance.y,
						(int)player->size_.w, (int)player->size_.h, 0, player->color_, kFillModeSolid);
				}
				else {
					player->Draw();
					player->ChargeShotDraw();
				}
			}
			else if (isHitWall == 1) {
				//BG
				for (int i = 0; i < 30; i++) {
					Novice::DrawLine(i * 50 - 190 + (int)randDistance.x, -100, i * 50 - 190 + (int)randDistance.x, 900, WHITE);
				}
				for (int j = 0; j < 20; j++) {
					Novice::DrawLine(-100, j * 50 - 190 + (int)randDistance.y, 1400, j * 50 - 190 + (int)randDistance.y, WHITE);
				}
				DrawInstruction(effect);
				//par
				for (int i = 0; i < kParticleNum; i++) {
					Novice::DrawEllipse(int(particle[i]->pos_.x + randDistance.x), int(particle[i]->pos_.y + randDistance.y),
						particle[i]->randRadius, particle[i]->randRadius, 0, particle[i]->color_, kFillModeSolid);
				}
				//bullet
				Novice::DrawEllipse(int(player->bullet->pos.x) + (int)randDistance.x, int(player->bullet->pos.y) + (int)randDistance.y,
					player->bullet->radius, player->bullet->radius, 0, player->bullet->color, kFillModeSolid);
				//player
				Novice::DrawEllipse((int)player->pos_.x + (int)randDistance.x, (int)player->pos_.y + (int)randDistance.y,
					(int)player->size_.w, (int)player->size_.h, 0, player->color_, kFillModeSolid);
			}
		}



		if (Novice::IsPressMouse(0)) {
			Novice::DrawBox((int)player->pos_.x + 60, (int)player->pos_.y - (endGaugeTimer - 40), 25, endGaugeTimer, 0, BLACK, kFillModeWireFrame);
			Novice::DrawBox((int)player->pos_.x + 60, (int)player->pos_.y + 39 + chargeGaugeTop, 24, chargeGaugeBot, 0, gaugeColor, kFillModeSolid);
		}

#ifdef _DEBUG

		Novice::ScreenPrintf(0, 0, "%d", chargeEndTimer);
		Novice::ScreenPrintf(0, 20, "chargeShotStart = %d", chargeShotStart);
		Novice::ScreenPrintf(0, 40, "isSHot = %d", isShot);
		Novice::ScreenPrintf(0, 60, "distance = %f", fabsf(particle[99]->pos_.x - player->pos_.x));
		Novice::ScreenPrintf(0, 80, "SPD = %f", particle[99]->spd_);
		Novice::ScreenPrintf(0, 100, "effect = %d", effect);
		Novice::ScreenPrintf(0, 120, "isPressing = %d", isPressingMouse);

#endif // !1


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();

	delete player;
	for (int i = 0; i < kParticleNum; i++) {
		delete particle[i];
	}

	return 0;
}
