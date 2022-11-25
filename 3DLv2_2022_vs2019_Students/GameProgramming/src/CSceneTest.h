#ifndef CSCENETEST_H
#define CSCENETEST_H
#include "CScene.h"
#include "CXCharacter.h"
#include "CActionCamera.h"
#include "CPaladin.h"
#include "CColliderMesh.h"
#include "CText.h"

/*
ゲームのシーン
*/
class CSceneTest : public CScene {
public:
	static CText* Text();
	CSceneTest()
		: mActionCamera(3.0f,-15.0f,180.0f)
	{}
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
private:
	static CText sText;
	CColliderMesh mColliderMesh;
	CPaladin* mpPlayer;
	CActionCamera mActionCamera;
	CModel mGround;
	CVector mScale;
	bool mPushFlg;
	float mOldMousePosX;
	CTransform mTransform;
	CModelX mModelX;
	//キャラクタのインスタンス
	//CXCharacter mXCharacter;
};

#endif