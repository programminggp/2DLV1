#ifndef CSCENETEST_H
#define CSCENETEST_H
#include "CScene.h"
#include "CXCharacter.h"

/*
ゲームのシーン
*/
class CSceneTest : public CScene {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
private:
	CVector mScale; //拡大縮小倍率
	bool mPushFlg;
	float mOldMousePosX;
	CTransform mTransform; //回転縮小用行列
	CModelX mModelX; //Xモデルデータ
	CXCharacter mXCharacter; 	//キャラクタのインスタンス
};
#endif

