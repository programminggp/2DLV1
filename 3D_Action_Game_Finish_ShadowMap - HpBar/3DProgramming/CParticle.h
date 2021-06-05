#ifndef CPARTICLE_H
#define CPARTICLE_H

#include "CBillBoard.h"
//色
#define PARTICLE_COLOR 0.9f, 0.9f, 0.4f, 0.4f
//寿命 10フレーム
#define PARTICLE_LIFE 10
//大きさ
#define PARTICLE_SCALE 0.2, 0.2, 0.0f
//移動の速さ
#define PARTICLE_VELOCITY 0.025f
/*
パーティクルクラス
*/
class CParticle : public CBillBoard {
public:
	//移動の向き
	CVector3 mVelocity;
	//色
	CVector4 mColor;
	//寿命
	int mLife;
	//コンストラクタ
	CParticle() {}
	CParticle(CTexture *texture
		, const CVector3& position
		, const CVector3& velocity
		, const CVector3& scale = CVector3(PARTICLE_SCALE)
		, const CVector4& color = CVector4(PARTICLE_COLOR)
		, int life = PARTICLE_LIFE);
	void Update();
	void Render();
};
/*
パーティクル発生クラス
*/
class CEmitter {
public:
	//画像
	CTexture mTexture;
	//放出数
	int mNums;
	//移動の速さ
	float mVelocity;
	//大きさ
	CVector3 mScale;
	//色
	CVector4 mColor;
	//寿命
	int mLife;
	//コンストラクタ
	CEmitter(){}
	CEmitter(char* texture
		, int nums
		, float velocity = PARTICLE_VELOCITY
		, const CVector3& scale = CVector3(PARTICLE_SCALE)
		, const CVector4& color = CVector4(PARTICLE_COLOR)
		, int life = PARTICLE_LIFE);
	//パーティクルを発生させる
	void Emit(const CVector3& position);
};

#endif
