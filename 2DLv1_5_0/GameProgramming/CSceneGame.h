#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CPlayer.h"
#include "CBackGround.h"
#include "CTexture.h"
#include "CEnemy.h"
#include <vector>
#include "CInput.h"
#include "CCamera.h"

#define CHIPSIZE 16

//クラスの定義
class CSceneGame: public CScene {
	CCamera mCamera;
public:
	static std::vector<CCharacter*> mCharacters;
	//変数の宣言
	CInput mInput;

	CSceneGame();

	~CSceneGame();

	//メソッド（プログラム）の宣言
	void Init();
	void Update();
	void Render();
};

extern CTexture TexBomberman;;

#endif
