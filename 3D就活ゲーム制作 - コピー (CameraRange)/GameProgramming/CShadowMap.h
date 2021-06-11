#pragma once

#include "CSceneRace.h"
#include "CObj.h"

class CShadowMap : public CSceneRace
{
	CObj *mpPlayer;
	CObj *mpGround;
	GLuint dtex;
public:
	~CShadowMap();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};