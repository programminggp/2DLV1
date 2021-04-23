#ifndef CSCENERACE_H
#define CSCENERACE_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCameraRange.h"
#include "CCameraPos.h"
#include "CRigidObj.h"
//CSound.hをインクルードしたら音の再生の動作が軽くなった？
#include "CSound.h"
#include "CSceneGame.h"

#define ENEMYS_AMOUNT 7-2 //0以下には設定できない
/*
ゲームのシーン
*/
class CSceneRace : public CScene {
public:
	//次のシーンの取得
	EScene GetNextScene();

	~CSceneRace();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//ミニマップ関連の処理
	void RenderMiniMap();
	//バックミラーの描画
	void RenderBackMirror();
	
	CModel mSky;
	CModel mRock;
	CModel mRover;
	CModel mCarRed;
	CModel mCarBlue;
	CModel mCarGreen;
	CModel mCarYellow;
	CModel mCarPink;
	CModel mCarCyan;
	CModel mCarWhite;
	CModel mCarBlack;//もはやシルエット
	CModel mCarGray;
	CModel mCube;
	CModel mPlane;
	CModel mStairs;//階段
	CModel mTarget;//的
	CModel mOnBlock;//OFFになると消える

	CModel mCube2;//本当に透明
	CModel mCube3;//窓っぽい色

	CModel mCheckPoint;//処理軽減の為に1枚だけのポリゴンで、透明タイルを表現

	CModel mWater;//水タイル

	//ジャンプ床に活用できる気がする…
	CModel mSpringS;//ばね
	CModel mSpringL;//ばね伸び

	CModel mTileBlack;//黒い床
	CModel mTileWhite;//白い床

	CModel mCarsol;//矢印(ミニマップ)
	CModel mCarsol_Enemy;//敵の矢印(ミニマップ)
	CModel mMiniGoal;//ゴールIcon(ミニマップ)

	CModel mCource01;//コース01
	CModel mGrass01;//芝生01
	CModel mFence01;//柵
	CModel mRWTile;//芝生とアスファルトの境目
	
	CModel mFenceTop;//柵の上面
	CModel mFenceSide;//柵の側面
	CModel mStuff;//内側の柵の空間を詰める物

	CModel mPole;//ポール

	CModel mDashBoard;//加速床

	CPlayer *mPlayer;
	CEnemy *mEnemys[ENEMYS_AMOUNT];
	CCameraRange *mCamRange;
	CCameraPos *mCam;

	CSound BGM;
	CSound SoundCountDown;
	CSound SoundStart;
	CSound SoundGoal;
	
	float mCamY;//プレイヤーの周りをグルグル(水平方向に)

	bool mPutCol;

	int mFrame;
	int mCountDown;
	bool isStartRace, isGoal;
	int mTime, mTime_Output;
	static int mBestTime;
	int mLap, mMaxLap;
	bool isNewRecord;
	static int mRecord_A, mRecord_B, mRecord_C, mRecord_D, mRecord_E, mRecord_F;

	int mCamPoV;

	//コース2のマテリアル
	CModel msumple2;

	int mTextBlinkTime;
	bool isRendPoint;
	
	bool isPause;

	int mRanking;
	int mAfterGoalTime;

	bool isRender_BackMirror;

	
	CModel mCource02Road;
	CModel mCource02Wall;
	CModel mCource02Jump;

	CModel mCource03Road;
	CModel mCource03Wall;
	CModel mCource03Fence;
	
	CModel mCource04;
	CModel mCource04Water;
	CModel mCource04A;

	CModel mJumper01;//ジャンプ台
	
	//平ら
	CModel mTile_Curve01_Floor;
	CModel mTile_Curve02_Floor;
	CModel mTile_Curve03_Floor;
	CModel mTile_Curve04_Floor;
	CModel mTile_Straight01_Floor;
	CModel mTile_Straight02_Floor;
	CModel mTile_Curve01_Wall;
	CModel mTile_Curve02_Wall;
	CModel mTile_Curve03_Wall;
	CModel mTile_Curve04_Wall;
	CModel mTile_Straight01_Wall;
	CModel mTile_Straight02_Wall;
	//坂
	CModel mTile_Slope01_Floor;
	CModel mTile_Slope02_Floor;
	CModel mTile_Slope03_Floor;
	CModel mTile_Slope04_Floor;
	CModel mTile_Slope01_Wall;
	CModel mTile_Slope02_Wall;
	CModel mTile_Slope03_Wall;
	CModel mTile_Slope04_Wall;
	//でかい
	CModel mTile_Wide_Floor;
	CModel mTile_Wide_Wall;
	CModel mBlock_Floor;
	CModel mBlock_Wall;
	
	CModel mCource05Mountain;
	CModel mCource05Wall;
	CModel mCource05Road;
	CModel mCource05Lake;
	CModel mCource05Grass_Floor;
	CModel mCource05Grass_Wall;
	CModel mCource05GoalTile;

	CModel mSign_Left;
	CModel mSign_Right;

	CModel mSumpluuu;
};
#endif
