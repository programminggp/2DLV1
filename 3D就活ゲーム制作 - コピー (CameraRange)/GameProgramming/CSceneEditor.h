#ifndef CSCENEEDITOR_H
#define CSCENEEDITOR_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCameraRange.h"
#include "CCameraPos.h"
#include "CSound.h"

/*
エディター画面
*/
class CSceneEditor : public CScene {	
private:
	float mCamY;//プレイヤーの周りを回転(水平方向に)	
	int mTextBlinkTime;
	bool isPause;
	bool mPutCol;//当たり判定の描画のON・OFF	
protected:
	CModel mRover;
	CModel mCarRed;
	CModel mCarBlue;
	CModel mCarGreen;
	CModel mCarYellow;
	CModel mCarPink;
	CModel mCarCyan;
	CModel mCarWhite;
	CModel mCarBlack;
	CModel mCarGray;
	CModel mPlane;
	CModel mCheckPoint;//ポリゴン1枚のみ、透明
	CModel mTileBlack;//黒い床
	CModel mTileWhite;//白い床
	CModel mCarsol;//矢印(ミニマップ)
	CModel mCarsol_Enemy;//敵の矢印(ミニマップ)
	CModel mMiniGoal;//ゴールIcon(ミニマップ)
	CModel mCource01;//コース01
	CModel mGrass01;//芝生01
	CModel mRWTile;//芝生とアスファルトの境目
	CModel mFenceTop;//柵の上面
	CModel mFenceSide;//柵の側面
	CModel mPole;//ポール
	CModel mDashBoard;//加速床

	CPlayer *mPlayer;
	//CEnemy *mEnemys[ENEMYS_AMOUNT];
	CCameraRange *mCamRange;
	CCameraPos *mCam;

	CSound BGM;
	CSound SoundCountDown;
	CSound SoundStart;
	CSound SoundGoal;

	//コース2,3のモデル
	CModel mCource02Road;
	CModel mCource02Wall;
	CModel mCource02Jump;
	CModel mCource03Road;
	CModel mCource03Wall;
	CModel mCource03Fence;

	CModel mJumper01;//ジャンプ台
	//平たいる
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
	//坂系
	CModel mTile_Slope01_Floor;
	CModel mTile_Slope02_Floor;
	CModel mTile_Slope03_Floor;
	CModel mTile_Slope04_Floor;
	CModel mTile_Slope01_Wall;
	CModel mTile_Slope02_Wall;
	CModel mTile_Slope03_Wall;
	CModel mTile_Slope04_Wall;
	//でかめのタイル
	CModel mTile_Wide_Floor;
	CModel mTile_Wide_Wall;
	CModel mBlock_Floor;
	CModel mBlock_Wall;
	//コース5のモデル
	CModel mCource05Mountain;
	CModel mCource05Wall;
	CModel mCource05Road;
	CModel mCource05Lake;
	CModel mCource05Grass_Floor;
	CModel mCource05Grass_Wall;
	CModel mCource05GoalTile;
	//標識
	CModel mSign_Left;
	CModel mSign_Right;
public:
	//次のシーンの取得
	EScene GetNextScene();

	~CSceneEditor();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//ミニマップ関連の処理
	void RenderMiniMap();
	//バックミラーの描画
	void RenderBackMirror();
};

#endif
