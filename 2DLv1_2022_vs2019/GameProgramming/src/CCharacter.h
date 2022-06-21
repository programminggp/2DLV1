#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include <stdio.h>

#define VELOCITY 2.0f	//移動速度

class CCharacter : public CRectangle
{
public:
	enum class ETag
	{
		EZERO,		//初期値
		EBULLET,	//弾
		EENEMY,		//敵
		EPLAYER,	//プレイヤー
		ETURN,		//折り返し
		EBLOCK,		//ブロック
	};
	enum class EState	//状態
	{
		EMOVE,	//移動
		ESTOP,	//停止
		EJUMP,	//ジャンプ
		ECRY,	//泣く
	};
protected:
	float mVx;	//X軸速度
	float mVy;	//Y軸速度
	bool mEnabled;
	ETag mTag;
	EState mState;
private:
	CTexture *mpTexture;
	int mLeft, mRight, mBottom, mTop;
public:
	EState State();	//状態を取得する
	bool Enabled();
	ETag Tag();
	//衝突処理２
	virtual void Collision() {};
	//衝突処理４
	//Collision(自分のポインタ, 衝突相手のポインタ)
	virtual void Collision(CCharacter* m, CCharacter* o) {};
	virtual void Update() = 0;
	CCharacter();
	CTexture* Texture();
	void Texture(CTexture *pTexture, int left, int right, int bottom, int top);
	virtual void Render();
	void Move();
};