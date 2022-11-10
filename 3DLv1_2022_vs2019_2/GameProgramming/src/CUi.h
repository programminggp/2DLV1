#pragma once
#include "CFont.h"
/*
* CUi
* ユーザーインタフェースクラス
*/
class CUi
{
public:
	void PosY(float f);
	void RotX(float f);
	void RotY(float f);
	//2D描画スタート
	//Start2D(左座標, 右座標, 下座標, 上座標)
	void Start2D(float left, float right, float bottom, float top);
	//2D描画終了
	void End2D();

	//ゲームクリア表示
	void Clear();
	//ゲームオーバー表示
	void Over();
	//スタート表示
	void Start();
	//Enemy(敵の数)
	void Enemy(int enemy);
	CUi();
	void Hp(int hp);
	//Time(時間)
	void Time(int time);
	void Render();
private:
	float mPosY;	//Y座標
	float mRotX;	//X回転値
	float mRotY;	//Y回転値
	int mEnemy;	//敵の数
	int mHp;
	int mTime;	//経過時間
	CFont mFont;
};
