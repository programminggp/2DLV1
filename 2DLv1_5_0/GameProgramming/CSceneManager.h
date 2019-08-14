#ifndef CSCENEMANGER
#define CSCENEMANGER
#include "CScene.h"
#include "CInput.h"

//クラスの定義
class CSceneManager : public CScene {
	CScene *mpScene;
public:
	//変数の宣言
	CInput mInput;

	CSceneManager();

	~CSceneManager();

	//メソッド（プログラム）の宣言
	void Init();
	void Update();
	void Render();
};

#endif
