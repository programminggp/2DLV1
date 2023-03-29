#pragma once
#include "CFont.h"
#include "CFont2.h"
#include "CHeart.h"
#include "CStamina.h"
#include "CGage.h"
#include "CBossHp.h"
#include "CBossHpGage.h"
/*
* CUi
* ユーザーインタフェースクラス
*/
class CUi:public CRectangle
{
private:
	CBossHpGage mBossHpGage;
	CBossHp mBossHp;
	CStamina mStamina;
	CGage mGage;
	CHeart mHeart;
	int mBEhp;  //ボスのHP
	int mEnemy;	//敵の数
	int mHp;    //プレイヤーのHP
	int mStaminagage; //プレイヤーのスタミナ
	int mTime;	//経過時間
	CFont mFont;
	CFont2 mFont2;

public:
	CTexture mTexture100;
	CTexture mTexture101;
	CTexture mTexture102;
	CTexture mTexture103;
	CTexture mTexture104;
	//コンストラクタ
	CUi();
	//デストラクタ
	~CUi();

	//ゲームクリア表示
	void Clear();
	//ゲームオーバー表示
	void Over();
	//スタート表示
	void Start();

	//Enemy(敵の数)
	void Enemy(int enemy);
	//Hp(体力)
	void Hp(int hp);
	//Stamina(スタミナ)
	void Stamina(int stamina);
	//BossHp(ボスHP)
	void BEhp(int behp);
	//Time(時間)
	void Time(int time);
	//リザルト
	void DrawResult();
	void Render();
};
