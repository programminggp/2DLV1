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
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};
