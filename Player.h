#pragma once
#include "Struct.h"
#include "Bullet.h"

class Player
{
private:
	// 座標、速度、半径
	TransForm player_;
	// Bulletクラスの包含
	Bullet* bullet_;
	// 生存フラグ
	int isAlive;

public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();
	// 初期化
	void Initialization();
	// 更新処理
	void Update(char* keys, char* preKeys);
	// 移動
	void Move(char* keys, char* preKeys);
	// 球の発射
	void Shot(char* keys, char* preKeys);
	// 描画処理
	void Draw();
	// 当たり判定
	void CircleCollision(float posXA, float posYA, float radiusA, float posXB, float posYB, float radiusB);


	// 球の座標を取得
	float GetBulletPosX(int num) {
		return bullet_->GetPosX(num);
	}
	float GetBulletPosY(int num) {
		return bullet_->GetPosY(num);
	}
	// 弾の半径を取得
	float GetBulletRadius(int num) { return bullet_->GetRadius(num);
	}

	// 座標を取得する
	float GetPosX() { return player_.x; }
	float GetPosY() { return player_.y; }
	float GetRadius() { return player_.radius; }
	// 生存フラグを取得する
	int GetAlive() { return isAlive; }
};

