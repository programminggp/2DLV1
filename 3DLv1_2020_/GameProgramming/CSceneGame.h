#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CVector.h"
//モデルクラスのインクルード
#include "CModel.h"
//
#include "CCharacter.h"
//
#include "CPlayer.h"
//
#include "CColliderTriangle.h"
/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//三角コライダの作成
	CColliderTriangle mColliderTriangle;
	CColliderTriangle mColliderTriangle2;
	//C5モデル
	CModel mModelC5;
	CModel mBackGround;
	//モデルクラスのインスタンス作成
	CModel mModel;
	//
//	CCharacter mCharacter;
	CPlayer mPlayer;

	CVector mEye;
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
