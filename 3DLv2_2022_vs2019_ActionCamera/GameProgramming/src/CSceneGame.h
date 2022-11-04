#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CActionCamera.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
private:
	CActionCamera mActionCamera;
	CXEnemy mEnemy;
	//�L�����N�^�̃C���X�^���X
	CXPlayer mPlayer;
	CText mFont;

public:
	CSceneGame()
		: mActionCamera(5.0f, -15.0f, 180.0f)
	{}
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif