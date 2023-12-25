#include "CSceneGame.h"
//OpenGL
#include "gl/freeglut.h"
#include "CVector.h"
#include "CKey.h"
#include "CMatrix.h"
#include "CTaskManager.h"
#include "CUtil.h"
//
#include "CCollisionManager.h"
//
#include "CCamera.h"
//
#include "CXPlayer.h"
//
#include "CFelguard.h"


#include "CModel.h"
CModel gModel;
#include "CColliderMesh.h"
CColliderMesh gColliderMesh;
CMatrix gMatrix;


void gRender()
{
	CSceneGame::Render();
}


void CSceneGame::Init() {
	gModel.Load("res\\caernarfon-castle\\CaernarfonCastle1.obj", "res\\caernarfon-castle\\CaernarfonCastle1.mtl", true);
//	gModel.Load("res\\sky.obj", "res\\sky.mtl", true);
	gColliderMesh.Set(nullptr, &gMatrix, &gModel);

	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

	const float size = 1.0f;
	new CXPlayer(CVector(105,10,100), CVector(), CVector(size, size, size));
	new CFelguard();
	new CCamera(CVector(0.0f, 4.0f, 0.0f), CVector(20.0f, 0.0f, 0.0f), 7.0f);

#define TEXWIDTH  8192  //�e�N�X�`����
#define TEXHEIGHT  6144  //�e�N�X�`������

	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.2f };  //�e�̐F
	float lightPos[] = { 100.0f,100.0f,100.0f };  //�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, gRender, shadowColor, lightPos);
}

void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	CTaskManager::Get()->TaskCollision();

	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();


	Render();
	//mShadowMap.Render();


	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();
}

void CSceneGame::Render()
{
//	gModel.Render();
	CTaskManager::Get()->Render();
	gModel.Render();

#ifdef _DEBUG
	//�R���C�_�̕`��
//	CCollisionManager::Get()->Render();
#endif


}

