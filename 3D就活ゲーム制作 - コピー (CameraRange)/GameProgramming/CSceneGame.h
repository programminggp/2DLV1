#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
//CSound.hをインクルードしたら音の再生の動作が軽くなった？
#include "CSound.h"
/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//次のシーンの取得
	EScene GetNextScene();

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

	CModel mSky;
	CModel mRock;
	CModel mRover;
	CModel mCube;
	CModel mPlane;
	CModel mStairs;//階段
	CModel mTarget;//的
	CModel mOnBlock;//OFFになると消える

	CModel mItem;
	CModel mItemGun;

	CModel mCube2;//本当に透明
	CModel mCube3;//窓っぽい色

	CModel mWater;//水タイル

	CModel mBoat;
	CModel mWarpPoint;
	CModel mSpringS;//ばね
	CModel mSpringL;//ばね伸び

	CPlayer *mPlayer;

	CSound BGM;

	int mBlockAmoX;//X座標の最大ブロック数
	int mBlockAmoY;//Y座標の最大ブロック数
	int mBlockAmoZ;//Z座標の最大ブロック数
	int mBlockAmount;//上の三つの積にする

	float mCamY;//プレイヤーの周りをグルグル(水平方向に)

	bool mPutCol;
};

#endif
