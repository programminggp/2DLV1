#ifndef CSCENETITLE_H
#define CSCENETITLE_H
#include "CText.h"
#include "CScene.h"
#include "CKey.h"
#include <Windows.h>
#include "CSound.h"
//・・・
#include "CSceneRace.h"

class CSceneTitle : public CScene {
private:
	int mCarsol_Pos;
	bool mStart;
	int mStartWaitTime;
	int mSelect_Step;//選択画面の何段階目か
	int mLevel;//敵のレベル
	int mCourceNum;

	int mCarsol_mode;

	CTexture Texture_GoldTrophy;
	CTexture Texture_SilverTrophy;
	CTexture Texture_BronzeTrophy;
	CTexture Texture_DetailGP;
	CTexture Texture_DetailTA;
public:
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();

	//次のシーンの取得
	EScene GetNextScene();
	
	CSound SoundMoveCarsol;
	CSound SoundDecide;
	CSound SoundCancel;
	
	//CPUの強さ
	enum ECPU_Level{
		EEASY = 1,//簡単
		ENORMAL,//普通
		EHARD,//難しい
	};
	static ECPU_Level mCPU_Level;

	//CPUの強さ
	enum ECource{
		ECOURCEEDITOR = 0,//エディター
		ECOURCE1,//コースA
		ECOURCE2,//コースB...
		ECOURCE3,
		ECOURCE4,
		ECOURCE5,		
	};
	static ECource mCource;

	//CPUの強さ
	enum EMode{
		EMODE_GRANDPRIX,//グランプリモード
		EMODE_TIMEATTACK,//タイムアタックモード
	};
	static EMode mMode;
		
	static int RecordHigh_Ranking;
};

#endif