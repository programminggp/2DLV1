#ifndef CSCENETEST_H
#define CSCENETEST_H
#include "CScene.h"
#include "CText.h"
#include "CKey.h"
#include <Windows.h>
#include "CSound.h"
#include "CModel.h"

class CSceneTest : public CScene {
private:
	CModel mCource05Road;
	CVector e, c, u;
public:
	CSceneTest()
		: e(0.0f, 20000.0f, 0.0f), c(0.0f, 0.0f, 0.0f), u(0.0f, 0.0f, 1.0f)
	{}

	~CSceneTest();

	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//���̃V�[���̎擾
	EScene GetNextScene();	
};

#endif