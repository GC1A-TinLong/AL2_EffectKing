#include <Novice.h>
#include <Player.h>
#include <Particle.h>

const char kWindowTitle[] = "GC1A_10_チョウ_テンロウ";

const int kParticleNum = 200;
const int kChargeNum = 60;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Player* player = new Player;

	Particle* particle[kParticleNum]{};
	for (int i = 0; i < kParticleNum; i++) {
		particle[i] = new Particle;
		//particle[i]->Initialization();
	}

	int bloomStart = 0;

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

		player->Control(keys, preKeys);

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			bloomStart = 1;						//Start Flag
		}
		if (bloomStart == 1) {
			for (int i = 0; i < kParticleNum; i++) {
				particle[i]->bufStart_ = 1;		//Effect keep going flag
				particle[i]->bloomStart_ = 1;
				particle[i]->spd_ = 1.5f;
			}
		}
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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(0, 0, 1280, 720, 0, 0x888888FF, kFillModeSolid);

		for (int i = 0; i < kParticleNum; i++) {
			particle[i]->Draw();
		}

		player->Draw();

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
