#include "Player.h"
#include "Novice.h"
#include <math.h>

// コンストラクタ
Player::Player()
{
	// 中心はX＝640、Y＝800
	player_.x = 640;
	player_.y = 500;
	// 半径は10，スピードは5；
	player_.radius = 20;
	player_.speed = 5;
	// 球の初期化
	bullet_ = new Bullet;
	// 生存フラグ
	isAlive = true;
}

// デストラクタ
Player::~Player()
{
	// Bulletクラスの解放
	delete bullet_;
}

// 初期化
void Player::Initialization()
{
	// 中心はX＝640、Y＝800
	player_.x = 640;
	player_.y = 500;
	// 半径は10，スピードは5；
	player_.radius = 20;
	player_.speed = 5;
	// 球の初期化
	bullet_ = new Bullet;
	// 生存フラグ
	isAlive = true;
}

// 更新処理
void Player::Update(char* keys, char* preKeys)
{
	if (isAlive) {
		// 移動
		Move(keys, preKeys);
		// 球の発射
		Shot(keys, preKeys);
	}
}

// 移動
void Player::Move(char* keys, char* preKeys)
{
	if (preKeys[DIK_W] && keys[DIK_W]) {
		player_.y -= player_.speed;
	}
	if (preKeys[DIK_S] && keys[DIK_S]) {
		player_.y += player_.speed;
	}
	if (preKeys[DIK_A] && keys[DIK_A]) {
		player_.x -= player_.speed;
	}
	if (preKeys[DIK_D] && keys[DIK_D]) {
		player_.x += player_.speed;
	}
}

// 発射
void Player::Shot(char* keys, char* preKeys)
{
	// 球の番号
	int bulletNum = 0;

	// スペースキーが押されたら
	if (preKeys[DIK_SPACE] && keys[DIK_SPACE]) {
		// 一発目を発射する
		if (!bullet_->GetIsShot(bulletNum)) {
			// 球の座標を自機に合わせる
			bullet_->SetPosX(player_.x, bulletNum);
			bullet_->SetPosY(player_.y, bulletNum);
			// 発射フラグをオンにする
			bullet_->SetIsShot(bulletNum);
		}

		// 一発目以降はカウントが0になり次第発射する
		for (int i = 1; i < 5 ; i++) {
			if (!bullet_->GetIsShot(i) && bullet_->GetShotCount(i) <= 0) {
				// 球の座標をプレイヤーに合わせる
				bullet_->SetPosX(player_.x, i);
				bullet_->SetPosY(player_.y, i);
				// 発射フラグをオンにする
				bullet_->SetIsShot(i);
			}
		}

	}
	// 球の更新処理
	bullet_->Update();
}

// 敵との当たり判定
void  Player::CircleCollision(float posXA, float posYA, float radiusA, float posXB, float posYB, float radiusB)
{
	float distans = 0;
	float distansX = 0;
	float distansY = 0;

	// 物体間の距離を求める
	distansX = posXA - posXB;
	distansY = posYA - posYB;
	distans = sqrtf(distansX * distansX + distansY * distansY);

	// 距離が0になった（当たった)ら
	if (distans <= (radiusA + radiusB)) {
		// 生存フラグをfalseにする
		isAlive = false;
	}

}

// 描画処理
void Player::Draw()
{

	if (isAlive) {
		// 球の描画
		bullet_->Draw();

		// 自機の描画
		Novice::DrawEllipse(
			static_cast<int>(player_.x),
			static_cast<int>(player_.y),
			static_cast<int>(player_.radius),
			static_cast<int>(player_.radius),
			0.0f, RED,
			kFillModeSolid

		);
	}
}
