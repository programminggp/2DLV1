#pragma once
#include "CTexture.h"
#include "CCharacter3.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"
#include <vector>

#include "CSound.h"

#include "CVector.h"
#include "CModel.h"

#include "CTaskManager.h"

#include "CColliderTriangle.h"

#include "CColliderMesh.h"

#include "CUi.h"

#include "CModelX.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CPaladin.h"

//29
#include "CActionCamera.h"

#include "CDengeki.h"

class CApplication
{
private:
	CDengeki mDengeki;
	//29
	CActionCamera mActionCamera;

	CPaladin *mpPaladin;

	CModelX mKnight;
	//敵のインスタンス
	CXEnemy mXEnemy;
	//キャラクタのインスタンス
	CXPlayer mXPlayer;

	CMatrix mMatrix;
	CModelX mModelX;
	static CUi* spUi;	//UIクラスのポインタ
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;

	//三角コライダの作成
	//CColliderTriangle mColliderTriangle;
	//CColliderTriangle mColliderTriangle2;

	//モデルビューの逆行列
	static CMatrix mModelViewInverse;

	//C5モデル
	CModel mModelC5;

	//static CTaskManager mTaskManager;
//	CPlayer mPlayer;

	CModel mBackGround; //背景モデル
	CModel mModel;
	CVector mEye;

	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//ゲームオーバー
	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー
	};
	EState mState;
//	CCharacter mRectangle;
	CPlayer* mpPlayer;
	static CTexture mTexture;
	CEnemy* mpEnemy;
//	CBullet* mpBullet;
	CInput mInput;
	CFont mFont;
	//CCharacterのポインタの可変長配列
//	std::vector<CCharacter*> mCharacters;
public:
	~CApplication();
	static CUi* Ui();	//UIクラスのインスタンスを取得
	//モデルビュー行列の取得
	static const CMatrix& ModelViewInverse();
	//static CTaskManager* TaskManager();
	static CTexture* Texture();
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};