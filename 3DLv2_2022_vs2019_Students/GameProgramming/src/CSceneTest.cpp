#include "CSceneTest.h"
#include "CInput.h"

//���f���̃t�@�C����
#define MODELX_FILE "res\\felguard\\felguard-X.X"

void CSceneTest::Init() {
	//���f���f�[�^�ǂݍ���
	mModelX.Load(MODELX_FILE);
	//���f���f�[�^�ݒ�
	mXCharacter.Init(&mModelX);
}

void CSceneTest::Update() 
{
	//�J�����ݒ�
	gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);
	//�L�����N�^�X�V�E�`��
	mXCharacter.Update();
	mXCharacter.Render();
}

