#pragma once
#include "CFont.h"
/*
* CUi
* ユーザーインタフェースクラス
*/
class CUi
{
public:
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
	int mEnemy;	//敵の数
	int mHp;
	int mTime;	//経過時間
	CFont mFont;
};
