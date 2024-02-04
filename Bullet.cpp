#include "Bullet.h"
#include <Novice.h>

// コンストラクタ
Bullet::Bullet()
{
	for (int i = 0; i < 5; i++) {
		// 座標、速度、半径
		bullet_[i].x = 0;
		bullet_[i].y = 0;
		bullet_[i].speed = 10;
		bullet_[i].radius = 5;
		// 次の弾を発射するまでのカウント
		nextShotCount[i] = 10;
		// 弾が発射されているかのフラグ
		isShot[i] = false;
	}
}

// 更新処理
void Bullet::Update()
{
	// 弾が発射状態になったら上に移動
	for (int i = 0; i < 5; i++) {
		if (isShot[i]) {
			bullet_[i].y -= bullet_[i].speed;
			// 次の弾が発射されるまでのカウントをする
			nextShotCount[i + 1] -= 1;
			// 画面外に出たら発射状態をオフにする
			if (bullet_[i].y + bullet_[i].radius <= 0) {
				nextShotCount[i + 1] = 10;
				isShot[i] = false;
			}
		}
	}
}

//
void Bullet::Draw()
{
	// 発射状態のときのみ描画する
	for (int i = 0; i < 5; i++) {
		if (isShot[i]) {
			Novice::DrawEllipse(
				static_cast<int>(bullet_[i].x),
				static_cast<int>(bullet_[i].y),
				static_cast<int>(bullet_[i].radius),
				static_cast<int>(bullet_[i].radius),
				0.0f, RED,
				kFillModeSolid);
		}
	}

}

