#ifndef CPLAYER_H
#define CPLAYER_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"

class CPlayer :public CCharacter{
private:
	CVector mVCheckPositions[4];//mChecksに応じたリスポーン地点の座標
	CVector mVCheckRotations[4];//mChecksに応じたリスポーン地点の回転値

	//ジャンプ速度の変数
	float mVelocityJump;
	//ジャンプを当たり判定よりも早く処理させるもの
	//int mJumpPrio;

	bool isBoost;//ブースト中か(加速床で一定時間有効)
	float mBoostMaxSpeed;//ブーストで底上げされる最高速度の値
	int mBoostTime;//ブースト状態の効果時間
protected:
public:
	static CPlayer*mpPlayer;
	//デフォルトコンストラクタ
	CPlayer();

	//更新
	void Update();

	//プレイヤーの体の当たり判定
	CCollider mColBody;
	//プレイヤーのタイヤの当たり判定
	CCollider mColTire;

	//衝突処理
	void Collision(CCollider *mc, CCollider *yc);
	
	//移動速度
	float mADMoveX;
	float mWSMoveZ;
	float mCarSpeed;
	//回転速度
	float mTurnSpeed;
	
	CSound SoundJump;
	CSound SoundShot;
	CSound SoundItemGet;
	CSound SoundBoost;
	CSound SoundEngine;//エンジン音
	CSound SoundEngine_Turf;//芝生の上での音
	bool isSoundEngine;
	CSound SoundHorn;
	CSound SoundCollision;
	CSound SoundCollisionSmall;
	bool isRespawn;
	CSound SoundSink;
	bool isSink;

	//リスポーン地点の設定(チェックポイントの通過状況に応じてリスポーン地点は変化)
	void SetRespawnPoint(int checknumber, CVector position, CVector rotation);
	//所定の位置(スタート地点)に着く
	void GetReady();

	bool mFlyingMode;//デバッグ用：自由落下を無効化

	int mChecks;
	bool isTouchGoal;//ゴール地点に入っているか
	int mGoalTime;
	int mRank;

	

	bool CanMove;//プレイヤーが操作可能か否か(カウントダウン前・ゴール後などは否)
	
	//コライダの更新
	void TaskCollision();

	enum Sound_Engine{
		ENONE,//初期値
		EONGRASS,//芝生の上
		ENOTONGRASS,//芝生の上でない
	};
	Sound_Engine mSound_Engine, mSound_Engine_Prev;//接触状況,1f前の〃	
};

#endif