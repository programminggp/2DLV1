#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:

	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

};

#endif
