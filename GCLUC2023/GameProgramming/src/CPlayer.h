#pragma once
#include "CCharacter.h"
#include "CInput.h"
#include "CMagicBullet.h"
/*
プレイヤークラス
キャラクタスを継承
*/
class CPlayer : public CCharacter
{
	friend CMagicBullet;
private:
	static CPlayer* spinstance;  //プレイヤーのインスタンス
	static int sHp;              //プレイヤーのHP
	static int sStamina;         //プレイヤーのスタミナ
	static int sCoolTime;        //スタミナのクールタイム

	int mInvincible;             //無敵カウンタ
	int mAnimationCount;         //アニメーションカウンタ

	float mJumpY;                //プレイヤーのジャンプ時のY座標
	CInput mInput;               //キー入力判定
	CMagicBullet* mpMagicBullet;

public:
	//コンストラクタ
	//CPlayer(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CPlayer(float x, float y, float w, float h, CTexture* pt);
	//~デストラクタ
	~CPlayer();

	//インスタンスのポインタの取得
	static CPlayer* Instance();
	//プレイヤーのHPを取得
	static int HP();
	//プレイヤーのスタミナを取得
	static int Stamina();

	//衝突処理
	void Collision(CCharacter* m, CCharacter* o);

	//更新処理
	void Update();

	//移動処理
	void Move();
	//ジャンプ処理
	void Jump();
	//アイドリング処理
	void Idling();
	//攻撃処理
	void Attack();
	//被弾処理
	void Damage();
	//死亡処理
	void Death();
};