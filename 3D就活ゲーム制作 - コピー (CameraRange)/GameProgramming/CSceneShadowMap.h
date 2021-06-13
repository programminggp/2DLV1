#pragma once

#include "CSceneRace.h"
#include "CObj.h"

class CSceneShadowMap : public CSceneRace
{
	CObj* mpPlayer;
	CObj* mpGround;
	GLuint mDepthTextureID;
public:
	~CSceneShadowMap();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};
