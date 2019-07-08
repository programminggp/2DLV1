#ifndef CSCENEGAME_H	//インクルードガード
#define CSCENEGAME_H	//インクルードガード

//CSceneクラスのインクルード
#include "CScene.h"

/*
ゲームシーンの定義
CSceneクラスを継承して
CSceneGameクラスを定義する
*/
class CSceneGame : public CScene {
public:
	/*
	インスタンスの更新処理を記述
	*/
	void Update();
};

#endif	//インクルードガード
