#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"

#include "Ckey.h"
//
#include "CMaterial.h"
//
#include "CCollisionManager.h"

CSceneGame::CSceneGame()
//	: mKnight(CVector(7.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f))
{
}

CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

//	CRes::sModelX.Load(MODEL_FILE);

	//�L�����N�^�[�Ƀ��f����ݒ�
//	mPlayer.Init(&CRes::sModelX);

}


void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//�Փˏ���
	CTaskManager::Get()->TaskCollision();
//	CCollisionManager::Get()->Collision();	

	CTaskManager::Get()->Render();

#ifdef _DEBUG
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
#endif

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();
	return;
}

