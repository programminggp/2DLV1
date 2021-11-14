#ifndef CSCENECHECK_H
#define CSCENECHECK_H
#include "CScene.h"
#include "CModel.h"
#include "CCameraRange.h"
#include "CCameraPos.h"

#include "CObjFloor.h"


/*
ゲームのシーン
*/
class CSceneCheck : public CScene {
private:
	CVector mEye;
	CVector mCameraRotation;

protected:

	CModel mCource01;//コース01

	CCameraRange *mCamRange;
	CCameraPos *mCam;

public:
	//次のシーンの取得
	EScene GetNextScene();

	~CSceneCheck();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

};
#endif
