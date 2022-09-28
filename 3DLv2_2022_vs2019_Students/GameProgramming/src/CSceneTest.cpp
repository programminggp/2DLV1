#include "CSceneTest.h"
#include "CInput.h"

//モデルのファイル名
#define MODELX_FILE "res\\felguard\\felguard-X.X"

void CSceneTest::Init() {
	//モデルデータ読み込み
	mModelX.Load(MODELX_FILE);
	//モデルデータ設定
	mXCharacter.Init(&mModelX);
}

void CSceneTest::Update() 
{
	//カメラ設定
	gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);
	//キャラクタ更新・描画
	mXCharacter.Update();
	mXCharacter.Render();
}

