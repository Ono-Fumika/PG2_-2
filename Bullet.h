#pragma once
#include "Struct.h"

class Bullet
{
private:
	// 座標、速度、半径
	TransForm bullet_[5];
	// 次の弾を発射するまでのカウント
	int nextShotCount[5];
	// 弾が発射されているかのフラグ
	double isShot[5];

public:
	// コンストラクタ
	Bullet();
	// 更新処理
	void Update();
	// 描画処理
	void Draw();

	// 発射フラグを取得
	bool GetIsShot(int num) { return isShot[num]; }
	// 発射フラグの変更
	bool SetIsShot(int num) {
		isShot[num] = true;
		return isShot[num];
	}
	// 球の座標を取得
	float GetPosX(int num) {
		return bullet_[num].x;
	}
	float GetPosY(int num) {
		return bullet_[num].y;
	}
	// 弾の半径を取得
	float GetRadius(int num) { return bullet_[num].radius; }

	// 球の座標を変更
	float SetPosX(float posX,int num) {
		bullet_[num].x = posX;
		return bullet_[num].x;
	}
	float SetPosY(float posY,int num) {
		bullet_[num].y = posY;
		return bullet_[num].y;
	}
	// 発射までのカウントを取得
	int GetShotCount(int num) { return nextShotCount[num]; }
};

