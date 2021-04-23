#ifndef CSCENERACE2_H
#define CSCENERACE2_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy.h"
//CSound.hをインクルードしたら音の再生の動作が軽くなった？
#include "CSound.h"
#include "CSceneGame.h"
/*
ゲームのシーン
*/
class CSceneRace2 : public CScene {
public:
	//次のシーンの取得
	EScene GetNextScene();

	~CSceneRace2();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//ミニマップ関連の処理
	void RenderMiniMap();
	
	CModel mMiami;

	CModel mSky;
	CModel mRock;
	CModel mRover;
	CModel mCarRed;
	CModel mCarBlue;
	CModel mCube;
	CModel mPlane;
	CModel mStairs;//階段
	CModel mTarget;//的
	CModel mOnBlock;//OFFになると消える

	CModel mItem;
	

	CModel mCube2;//本当に透明
	CModel mCube3;//窓っぽい色

	CModel mCheckPoint;//処理軽減の為に1枚だけのポリゴンで、透明タイルを表現

	CModel mWater;//水タイル

	CModel mSpringS;//ばね
	CModel mSpringL;//ばね伸び

	CModel mTileBlack;//黒い床
	CModel mTileWhite;//白い床

	CModel mCarsol;//矢印(ミニマップ)
	CModel mMiniGoal;//ゴールIcon(ミニマップ)

	CModel mCource01;//コース01
	CModel mGrass01;//芝生01
	CModel mFence01;//柵
	CModel mRWTile;//芝生とアスファルトの境目
	
	CModel mFenceTop;//柵の上面
	CModel mFenceSide;//柵の側面

	CModel mPole;//ポール

	CModel mDashBoard;//加速する床

	CPlayer *mPlayer;

	CEnemy *mEnemy1;
	CEnemy *mEnemy2;

	CSound BGM;
	CSound SoundCountDown;
	CSound SoundStart;
	CSound SoundGoal;
	

	int mBlockAmoX;//X座標の最大ブロック数
	int mBlockAmoY;//Y座標の最大ブロック数
	int mBlockAmoZ;//Z座標の最大ブロック数
	int mBlockAmount;//上の三つの積にする

	float mCamY;//プレイヤーの周りをグルグル(水平方向に)

	bool mPutCol;

	int mFrame;
	int mCountDown;
	bool isStartRace;
	int mTime;
	int mBestTime;
	int mLap;
	bool isNewRecord;

	float mXXX, mYYY, mZZZ;
	float mXX0, mZZ0;

	CModel mSumple;

	int mCamPoV;
};

#endif
