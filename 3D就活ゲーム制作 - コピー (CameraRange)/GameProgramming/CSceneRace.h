#ifndef CSCENERACE_H
#define CSCENERACE_H
#include "CScene.h"
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCameraRange.h"
#include "CCameraPos.h"
#include "CSound.h"
#include "CObjFloor.h"


#include <stdlib.h>

#define ENEMYS_AMOUNT (5)//0以下には設定できない

#define RACES_PER_1CUP 3//1カップで行うレース数
#define COURCE_TOTAL 5//全コース数
#define LIST_SIZE (ENEMYS_AMOUNT+1)
/*
ゲームのシーン
*/
class CSceneRace : public CScene {
private:
	GLuint mFb;
	static bool isEnableShadow;//影の描画の有無
	static bool isEnableMiniMap;//ミニマップ表示のON・OFF
	static bool isEnableBackMirror;//バックミラー表示のON・OFF
	static bool isEnableSpeedometer;//速度計のON・OFF

	GLuint mDepthTextureID;

	float mCamY;//プレイヤーの周りを回転(水平方向に)	

	//スタート前のカウントダウン
	int mFrame;//60f=1秒
	int mCountDown;
	//コースタイム、ラップ関連
	bool isStartRace, isGoal;
	int mTime, mTime_Output;


	static int mBestTime;
	int mLap, mMaxLap;
	bool isNewRecord;
	int mTextBlinkTime;//テキストの点滅に関わる変数

	bool isPause;
	int mPause_SelectCarsol;
	int mPause_OptionCarsol;
	enum EPauseScreen{
		EPAUSE,//ポーズ画面(選択肢がresume,option,quit)
		EOPTION,//オプション画面(設定を変更できる画面)
	};
	EPauseScreen mPauseScreen;

	int mRanking;
	int mAfterGoalTime;

	//デバッグコマンド用の変数
	bool mPutCol;//当たり判定の描画のON・OFF
	
	bool isFadeIn, isFadeOut;
	int isBlackOutTime;

	bool isOpening;
	int mTime_Opening;

	enum ECameraAngle{
		EANGLE_FRONTCAR,
		EANGLE_THIRDPERSON
	};
	ECameraAngle mCameraAngle;

	int mPushEnter_WaitTime;
	bool isGoaledAll;//全員ゴールしたか
	bool isResult_FinalRace;//最終結果(グランプリモードのみ)
	bool canPushEnter;

	CTexture Texture_GoldTrophy;
	CTexture Texture_SilverTrophy;
	CTexture Texture_BronzeTrophy;
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
	CModel mGoalTile01;
	CModel mCurb01;//紅白の縁石
	CModel mFenceTop;//柵の上面
	CModel mFenceSide;//柵の側面
	CModel mPole;//ポール
	CModel mDashBoard;//加速床

	CPlayer *mPlayer;
	CEnemy *mEnemys[ENEMYS_AMOUNT];
	CCameraRange *mCamRange;
	CCameraPos *mCam;

	CSound BGM;
	CSound JingleOpening;
	CSound SoundCountDown;
	CSound SoundStart;
	CSound SoundGoal;
	CSound SoundMoveCarsol;
	CSound SoundDecide;
	CSound SoundPauseOn;
	CSound SoundPauseOff;


	//コース2,3のモデル
	CModel mCource02Road;
	CModel mCource02Wall;
	CModel mCource02Jump;
	CModel mCource03Road;
	CModel mCource03Wall;
	CModel mCource03Fence;

	CModel mJumper01;//ジャンプ台
	//平らなタイル
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
	
	CModel mGoalGate;

	enum EStartPos{
		ESTARTPOS_RANDOM,//順位ランダムでスタート
		ESTARTPOS_TOP,//1位からのスタート
	};
	EStartPos mStartPos;

	int list[LIST_SIZE];//
public:
	//次のシーンの取得
	EScene GetNextScene();

	~CSceneRace();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//テキスト等の描画
	void Render();
	//ミニマップ関連の処理
	void RenderMiniMap();
	//バックミラーの描画
	void RenderBackMirror();
	//影の描画
	void RenderShadowMap();
	void RenderShadow();
	//フェードインをしてゲーム画面に入る
	void FadeIn();
	//他シーンに行く際の演出・処理
	void SceneChange();
	//CPU車の色の出力
	void PutCPUColor();
	
	//各コースのベストタイム
	static int mRecords[COURCE_TOTAL + 1];//0:edit 1～:cource1, 2, ...	
	static int mTotalPoint;//獲得した得点の合計
	static int mTotalPoint_Enemys[ENEMYS_AMOUNT];
	static int mCurrent_RaceNumber;//現在のレース数
};
#endif
