#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:

	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//���̃V�[���̎擾
	CScene::EScene CSceneGame::GetNextScene(){
		return mScene;
	}
};

#endif
