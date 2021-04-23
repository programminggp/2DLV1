#ifndef CSCENEGAMESTAGE2_H
#define CSCENEGAMESTAGE2_H

#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CSound.h"

/*
ステージ2の場面
*/
class CSceneGameStage2 : public CScene{
public:
	//次のシーンの取得
	EScene GetNextScene();

	~CSceneGameStage2();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

	CModel mSky;
	CModel mRock;
	CModel mRover;
	CModel mCube;
	CModel mPlane;
	
	CModel mGrass;//草原
	CModel mSoil; //土

	CModel mItem;
	CModel mItemGun;
	CModel mSpring;

	CModel mCube2;//本当に透明
	CModel mCube3;//窓っぽい色

	CModel mWater;//水タイル
	CModel mBridge;//橋

	CModel mInvWall;//見えない壁

	CModel mBoat;

	CModel mRoof;//屋根
	CModel mHouseWall;//家の壁
	CModel mDoor;//ドア
	CModel mKey;//鍵
	CModel mWindow;//窓

	CPlayer *mPlayer;

	int mBlockAmoX;//X座標の最大ブロック数
	int mBlockAmoY;//Y座標の最大ブロック数
	int mBlockAmoZ;//Z座標の最大ブロック数
	int mBlockAmount;//上の三つの積にする

	float mCamY;//プレイヤーの周りをグルグル(水平方向に)

	bool mPutCol;//衝突判定の表示

	CSound BGM;
};

#endif