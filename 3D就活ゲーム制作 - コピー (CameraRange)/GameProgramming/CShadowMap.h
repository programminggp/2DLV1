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
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};