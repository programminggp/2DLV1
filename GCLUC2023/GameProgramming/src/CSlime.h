#pragma once
#include "CCharacter.h"
#include "CTexture.h"
#include "CInput.h"
#include "CSlimeAttackBox.h"

#define SLIME "スライム3.png"
#define SLIMEX 1.5f 
#define SLIMEY 1.5f

class CSlime : public CCharacter
{
	friend CSlimeAttackBox;
protected:
public:
	EState State();	//状態を取得する
	static CSlime* Instance2();
	int SEhp();
	//敵の数を設定
	static void Num(int num);
	//敵の数を取得
	static int Num();
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
	CSlime(float x, float y, float w, float h, CTexture* pt);
	//更新処理
	void Update();
	static CTexture mTexture6;
	static CTexture* Texture6();
private:
	CSlimeAttackBox* mpSlimeAttackBox;
	CSlime* mpSlime;
	static CSlime* spInstance2;
	int sSEhp; //スライムのHP
	static int sNum;	//敵の数
	int mSlimeTime; //ダメージのスライム用の時間
	int mSlimeTime2; //移動のスライム用の時間
	int mSlimeTime3; //攻撃のスライム用の時間
	int mSlimeTime4; //死亡のスライム用の時間
	int mSlimeEattack; //攻撃持続時間
	int mSlimeInvincible; //無敵用のスライム用の時間
	EState mState; //状態
	float mSVx;	//X軸速度
	float mSVy;	//Y軸速度
	CInput mInput;
};