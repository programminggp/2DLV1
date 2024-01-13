#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"

#include "CTransform.h"
#include "CCollider.h"
#include "CTaskManager.h"
#include "CModel.h"

#include "CShadowMap.h"



/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {

	CText mFont;
	CShadowMap mShadowMap;

public:

	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//
	static void Render();
};

#endif
