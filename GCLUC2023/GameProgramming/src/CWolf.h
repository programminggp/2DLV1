#pragma once
#include "CCharacter.h"
#include "CTexture.h"
#include "CInput.h"
#include "CWolfAttackBox.h"

#define WOLFX 2.5f 
#define WOLFY 2.5f

class CWolf : public CCharacter
{
	friend CWolfAttackBox;
protected:
public:
	EState State();	//状態を取得する
	static CWolf* Instance3();
	int WEhp(); //オオカミのHP
	//敵の数を設定
	static void Num(int num);
	//敵の数を取得
	static int Num();
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
	CWolf(float x, float y, float w, float h, CTexture* pt);
	//更新処理
	void Update();
	static CTexture mTexture7;
	static CTexture* Texture7();
private:
	CWolfAttackBox* mpWolfAttackBox;
	static CWolf* spInstance3;
	int sWEhp; //オオカミのHP
	static int sNum;	//敵の数
	int mWolfTime; //ダメージのオオカミ用の時間
	int mWolfTime2; //攻撃のオオカミ用の時間
	int mWolfTime3; //死亡用のオオカミ用の時間
	int mWolfEattack; //攻撃持続時間
	int mWolfInvincible; //無敵用のオオカミ用の時間
	EState mState; //状態
	float mWVx;	//X軸速度
	float mWVy;	//Y軸速度
	float mWLR;
	CInput mInput;
};