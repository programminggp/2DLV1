#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"

CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);

}


void CSceneGame::Update() {
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(-2.0f, 10.0f, -30.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();


	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();

	return;
}

