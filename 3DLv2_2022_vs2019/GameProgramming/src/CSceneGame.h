#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {

	CText mFont;

public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif
