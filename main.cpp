#include <Novice.h>
#include "Player.h"
#include "Enemy.h"

const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 画像の読み取り
	int space = Novice::LoadTexture("./Resauce/space.png");
	int gameover = Novice::LoadTexture("./Resauce/gameover.png");
	int gameclear = Novice::LoadTexture("./Resauce/gameclear.png");
	int title = Novice::LoadTexture("./Resauce/title.png");

	// シーンの種類
	enum Scene {
		TITLE,
		STAGE,
		GAMECLEAR,
		GAMEOVER,
	};
	int sceneType = TITLE;

	// クラス
	Player* player = new Player;
	Enemy* enemy = new Enemy(100.0f,50.0f,40.0f,3.0f);
	Enemy* enemy2 = new Enemy(1000.0f, 150.0f, 40.0f, -3.0f);

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

		// タイトル画面
		if (sceneType == TITLE) {
			// スペースキーを押したらゲーム画面へ
			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE]) {
				sceneType = STAGE;
			}
			// 初期化
			player->Initialization();
			enemy->Initialization(100.0f, 50.0f, 40.0f, 3.0f);
			enemy2->Initialization(1000.0f, 150.0f, 40.0f, -3.0f);
		}

		// ゲーム画面
		if (sceneType == STAGE) {
			player->Update(keys, preKeys);
			enemy->Update();
			enemy2->Update();

			// 敵と自機の当たり判定
			player->CircleCollision(player->GetPosX(), player->GetPosY(), player->GetRadius(),
				enemy->GetPosX(), enemy->GetPosY(), enemy->GetRadius());

			player->CircleCollision(player->GetPosX(), player->GetPosY(), player->GetRadius(),
				enemy2->GetPosX(), enemy2->GetPosY(), enemy2->GetRadius());

			// 敵と弾の当たり判定
			for (int i = 0; i < 5; i++) {
				enemy->CircleCollision(player->GetBulletPosX(i), player->GetBulletPosY(i), player->GetBulletRadius(i),
					enemy->GetPosX(), enemy->GetPosY(), enemy->GetRadius());

				enemy2->CircleCollision(player->GetBulletPosX(i), player->GetBulletPosY(i), player->GetBulletRadius(i),
					enemy2->GetPosX(), enemy2->GetPosY(), enemy2->GetRadius());
			}

			// 自機が消えたらゲームオーバーシーンへ
			if (player->GetAlive() == false) {
				sceneType = GAMEOVER;
			}

			// 敵が全て消えたら
			if (enemy->GetLife() == 0 && enemy2->GetLife() == 0) {
				sceneType = GAMECLEAR;
			}
		}

		// ゲームオーバー
		if (sceneType == GAMEOVER) {
			// スペースキーを押したらタイトルへ
			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE]) {
				sceneType = TITLE;
			}
		}

		// ゲームクリア
		if (sceneType == GAMECLEAR) {
			// スペースキーを押したらタイトルへ
			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE]) {
				sceneType = TITLE;
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xd3d3d3FF, kFillModeSolid);

		// タイトル画面
		if (sceneType == TITLE) {
			Novice::DrawSprite(
				390, 200,
				title,
				1, 1, 0.0f,
				0xFFFFFFFF);

			Novice::DrawSprite(
				415, 500,
				space,
				1, 1, 0.0f,
				0xFFFFFFFF);
		}

		// ゲーム画面
		if (sceneType == STAGE) {
			player->Draw();
			enemy->Draw();
			enemy2->Draw();
		}

		// ゲームオーバー
		if (sceneType == GAMEOVER) {
			Novice::DrawSprite(
				390, 200,
				gameover,
				1, 1, 0.0f,
				0xFFFFFFFF);

			Novice::DrawSprite(
				400, 500,
				space,
				1, 1, 0.0f,
				0xFFFFFFFF);
		}

		// ゲームクリア
		if (sceneType == GAMECLEAR) {
			Novice::DrawSprite(
				390, 200,
				gameclear,
				1, 1, 0.0f,
				0xFFFFFFFF);

			Novice::DrawSprite(
				415, 500,
				space,
				1, 1, 0.0f,
				0xFFFFFFFF);
		}

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

	// メモリ解放
	delete player;
	delete enemy;
	delete enemy2;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
