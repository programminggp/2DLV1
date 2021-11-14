#ifndef CENEMY_H
#define CENEMY_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"
#include "CPoint.h"

class CEnemy :public CCharacter{
private:
	//プレイヤーの体の当たり判定
	CCollider mColBody;
	//プレイヤーのタイヤの当たり判定
	CCollider mColTire;

	//ジャンプ速度の変数
	float mVelocityJump;

	//移動速度
	float mADMoveX;
	float mWSMoveZ;
	float mCarSpeed;

	//回転速度
	float mTurnSpeed;

	float mStartPoint[3];//{ X,Y,Z }	

	bool isBoost;//ブースト中か(加速床で一定時間有効)
	float mBoostMaxSpeed;//ブーストで底上げされる最高速度の数値
	int mBoostTime;//ブースト状態が継続される時間

	//次のポイントまでに出す最高速度
	float mMaxSpeed_PtoP;
	
	//コライダ
	CCollider mSearch;

	CVector mVPoint;
	CVector mVPoint_prev;//一つ前の目標ポイント	
protected:

public:
	static CEnemy*mpEnemy;
	//デフォルトコンストラクタ
	CEnemy();

	//更新
	void Update();	

	//衝突処理
	void Collision(CCollider *mc, CCollider *yc);
	
	int mEnemyLap;
	bool isTouchGoal;//ゴール地点に入っているか
	bool isEnemyGoaled;
	int mGoalTime;
	int mRank;		
	int mPointTime;//最後にポイント通過してからの経過時間
	int mChecks;//チェックポイント
	bool CanMove;//プレイヤーが操作可能か否か(カウントダウン前・ゴール後などは否)
	
	//コライダの更新
	void TaskCollision();

	//誘導ポイント//中心、全エネミー共通のポイント
	static CPoint *mPoint;

	CPoint *mpPoint;//目指すポイント
	
	CPoint* GetNextPoint(CPoint *current_point, bool iscurrentpointlast);
	//現在の地点,誤差の有無,現在の目標地点が最後のポイントか
	void SetNextPoint(CPoint *current_point, int gap_amount, bool iscurrentpointlast);

	//敵のAI
	enum EEnemyAI{
		ENEWBIE, //一切減速しない
		EPRO, //適度に減速する
	};
	EEnemyAI mEnemyAI;

	//float corve;
};


#endif