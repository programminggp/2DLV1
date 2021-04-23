#include "CSceneTitle.h"

int CSceneTitle::mMode = 1; //コースやLap数の初期設定
int CSceneTitle::mDifficulty = 2; //敵AIの強さの初期設定　　1:EASY　2:NORMAL　3:HARD

////外部参照を解決させようとしているところ
//enum ECource CSceneTitle::mCource = ECOURCE1;
//ECource CSceneTitle::mCource = ECOURCE1;
//enum EMode CSceneTitle::mMode = E1LAP;

//次のシーンの取得
CScene::EScene CSceneTitle::GetNextScene(){
	return mScene;
}

void CSceneTitle::Render(){

}