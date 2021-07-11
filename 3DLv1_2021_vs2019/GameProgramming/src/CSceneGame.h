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
//
#include "CColliderMesh.h"
//
#include "CText.h"
/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	CText mText;

	//モデルからコライダを生成
	CColliderMesh mColliderMesh;
	//三角コライダの作成
	//削除CColliderTriangle mColliderTriangle;
	//削除CColliderTriangle mColliderTriangle2;
	//C5モデル
	CModel mModelC5;
	CModel mBackGround;
	CMatrix mBackGroundMatrix;
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
