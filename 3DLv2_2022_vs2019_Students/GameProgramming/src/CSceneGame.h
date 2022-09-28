#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CXEnemy.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
private:
	CXEnemy mEnemy;
	//�L�����N�^�̃C���X�^���X
	CXPlayer mPlayer;
	CText mFont;

public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif