#pragma once
#include "Struct.h"

class Enemy
{
private:
	// 座標、速度、半径
	TransForm enemy_;
	float speedY;
	// 残機表示の半径
	float lifeRadius;
	// エネミーが生きているかのフラグ
	int isEnemyAlive;
	// エネミーが復活するまでのカウント
	int respawnCount;
	// エネミーの残機
	int life;

public:
	// コンストラクタ
	Enemy(float posX,float posY,float radius,float speed);
	// 初期化
	void Initialization(float posX, float posY, float radius, float speed);
	// 更新処理
	void Update();
	// 移動
	void Move();
	// 描画処理
	void Draw();
	// 当たり判定
	void CircleCollision(float posXA, float posYA, float radiusA, float posXB, float posYB, float radiusB);

	// 座標を取得する
	float GetPosX() { return enemy_.x; }
	float GetPosY() { return enemy_.y; }
	float GetRadius() { return enemy_.radius; }
	// 生存フラグを取得する
	int GetAlive() { return isEnemyAlive; }
	// 残機を取得する
	int GetLife() { return life; }
};

