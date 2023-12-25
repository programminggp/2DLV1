#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"

#include "CTransform.h"
#include "CCollider.h"
#include "CTaskManager.h"
#include "CModel.h"

#include "CShadowMap.h"



/*
ゲームのシーン
*/
class CSceneGame : public CScene {

	CText mFont;
	CShadowMap mShadowMap;

public:

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//
	static void Render();
};

#endif
