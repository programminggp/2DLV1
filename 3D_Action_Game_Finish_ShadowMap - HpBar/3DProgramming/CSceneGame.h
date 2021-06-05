#ifndef CSCENEGAME_H
#define CSCENEGAME_H

#include "CModelX.h"
#include "CCamera.h"
#include "CTask.h"
#include "CMap.h"

class CSceneGame {
public:
	//*1
	//�}�b�v
	CMap mMap;
	//�J�����N���X�̃C���X�^���X
	CCamera mCamera;
	//X���f���̃C���X�^���X
	CModelX mModel;
	//�G�̃��f��
	CModelX mModelKnight;

	~CSceneGame() {
		//�^�X�N�}�l�[�W���̍폜
		CTaskManager::Get()->Destroy();
	}

	void Init();
	void Update();
	void Render();
};

#endif
