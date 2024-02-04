#include "Enemy.h"
#include "Novice.h"
#include <math.h>

// コンストラクタ
Enemy::Enemy(float posX, float posY, float radius, float speed)
{
	// 座標、速度、半径
	enemy_.x = posX;
	enemy_.y = posY;
	enemy_.radius = radius;
	enemy_.speed = speed;
	speedY = speed; 

	// 残機表示の半径
	lifeRadius = 10;
	// エネミーが生きているかのフラグ
	isEnemyAlive = true;
	// エネミーが復活するまでのカウント
	respawnCount = 50;
	// エネミーの残機
	life = 3;
}

// 初期化
void Enemy::Initialization(float posX, float posY, float radius, float speed)
{
	// 座標、速度、半径
	enemy_.x = posX;
	enemy_.y = posY;
	enemy_.radius = radius;
	enemy_.speed = speed;
	speedY = speed;

	// 残機表示の半径
	lifeRadius = 10;
	// エネミーが生きているかのフラグ
	isEnemyAlive = true;
	// エネミーが復活するまでのカウント
	respawnCount = 50;
	// エネミーの残機
	life = 3;
}

// 更新処理
void Enemy::Update()
{
	// 生存している間のみ動く
	if (isEnemyAlive) {
		Move();
	}

	// 生存していない場合
	if (!isEnemyAlive) {
		// ライフが0では無かったら
		if (life > 0) {
			// リスポーンカウントを数える
			respawnCount -= 1;

			// カウントが0になったら
			if (respawnCount <= 0) {
				// カウントをリセットする
				respawnCount = 50;
				// 生存フラグをtrueにする
				isEnemyAlive = true;
			}
		}
	}
}

// 移動処理
void Enemy::Move()
{
	// 上下に動かす
	enemy_.x += enemy_.speed;
	enemy_.y += speedY;

	// エネミーが画面外に出ないようにする
	if (enemy_.x + enemy_.radius >= 1280 || enemy_.x - enemy_.radius <= 0) {
		enemy_.speed = -enemy_.speed;
	}
	// エネミーが一定の範囲で上下するようにする
	if (enemy_.y + enemy_.radius >= 200 || enemy_.y - enemy_.radius <= 0) {
		speedY = -speedY;
	}

}

// 敵との当たり判定
void  Enemy::CircleCollision(float posXA, float posYA, float radiusA, float posXB, float posYB, float radiusB)
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
		if (isEnemyAlive && life > 0) {
			life -= 1;
		}
		isEnemyAlive = false;
	}

}

// 描画処理
void Enemy::Draw()
{

	// 生存している時のみ描画する
	if (isEnemyAlive) {
		Novice::DrawEllipse(
			static_cast<int>(enemy_.x),
			static_cast<int>(enemy_.y),
			static_cast<int>(enemy_.radius),
			static_cast<int>(enemy_.radius),
			0.0f, BLACK,
			kFillModeSolid
		);
	}

	// 残機表示
	//ライフが1の時
	if (life >= 1) {
		Novice::DrawEllipse(
			static_cast<int>(enemy_.x - enemy_.radius),
			static_cast<int>(enemy_.y - enemy_.radius - lifeRadius),
			static_cast<int>(lifeRadius),
			static_cast<int>(lifeRadius),
			0.0f, BLACK,
			kFillModeSolid
		);

		// ライフが2の時
		if (life >= 2) {
			Novice::DrawEllipse(
				static_cast<int>(enemy_.x),
				static_cast<int>(enemy_.y - enemy_.radius - lifeRadius),
				static_cast<int>(lifeRadius),
				static_cast<int>(lifeRadius),
				0.0f, BLACK,
				kFillModeSolid
			);
			
			// ライフが3の時
			if (life >= 3) {
				Novice::DrawEllipse(
					static_cast<int>(enemy_.x + enemy_.radius),
					static_cast<int>(enemy_.y - enemy_.radius - lifeRadius),
					static_cast<int>(lifeRadius),
					static_cast<int>(lifeRadius),
					0.0f, BLACK,
					kFillModeSolid
				);

			}
		}
	}

}

