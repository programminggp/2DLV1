#include "CSceneTest.h"
//#include "CRectangle.h"
#include "CCollisionManager.h"
#include "CRoadManager.h"
#include "CSceneTitle.h"

#define PLAYER_POSITION CVector(-3831.5f, 13.5f, 16011.5f)

//���̃V�[���̎擾
CScene::EScene CSceneTest::GetNextScene(){
	return mScene;
}

//�����������̃I�[�o�[���C�h
void CSceneTest::Init() {
	//�e�N�X�`���t�@�C����ǂݍ���
	//�t�H���g�̐ݒ�
	CText::mFont.Load("font\\font2nd.tga");
	CText::mFont.SetRowCol(8, 256 / 16);
	CText::mFont2.Load("font\\FontG.tga");
	CText::mFont2.SetRowCol(1, 4096 / 64);
	CText::mFont3.Load("font\\FontDIY.tga");//����t�H���g
	CText::mFont3.SetRowCol(8, 176 / 11);
	
	//�V�[���̐ݒ�
	mScene = ETEST;

	mCource05Road.Load("material\\racing_mat\\stage5\\cource05road2.obj", "material\\racing_mat\\stage5\\cource05road2.mtl");

	//�R�[�X�S�̂̃T�C�Y����ݒ�
	float mtsize = 35.0f;
	float height = 11.0f;
	CSceneTitle::mCource = CSceneTitle::ECOURCE5;
	new CRoadManager(&mCource05Road, CVector(0.0f, 21.0f, 0.0f), CVector(), CVector(mtsize, height, mtsize), PLAYER_POSITION, CVector(0.0f, 0.0f, -1.0f), 320.0f, 640.0f);//

}
//�X�V�����̃I�[�o�[���C�h
void CSceneTest::Update() {

	CTaskManager::Get()->Update();

	Render();//�e�L�X�g���̕`��

	if (CKey::Once(VK_RETURN))
	{
		CSceneTitle::mMode = CSceneTitle::EMODE_GRANDPRIX;
		CSceneTitle::mCource = CSceneTitle::ECOURCE5;
		mScene = CScene::ERACE5;
	}
}

#define CAMERA_V 100.0f

void CSceneTest::Render(){

	if (CKey::Push('W'))
	{
		e.mZ += CAMERA_V;
		c.mZ += CAMERA_V;
	}
	if (CKey::Push('S'))
	{
		e.mZ -= CAMERA_V;
		c.mZ -= CAMERA_V;
	}
	if (CKey::Push('A'))
	{
		e.mX += CAMERA_V;
		c.mX += CAMERA_V;
	}
	if (CKey::Push('D'))
	{
		e.mX -= CAMERA_V;
		c.mX -= CAMERA_V;
	}
	if (CKey::Push(VK_UP))
	{
		e.mY += CAMERA_V;
		c.mY += CAMERA_V;
	}
	if (CKey::Push(VK_DOWN))
	{
		e.mY -= CAMERA_V;
		c.mY -= CAMERA_V;
	}




	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);


	CTaskManager::Get()->Render();//�^�X�N	

			//�Փ˔���̕`��
	CollisionManager.Render();


	//2D�`��J�n
	Start2D(0, 800, 0, 600);	
	float col[] = { 1.0f, 1.0f, 1.0f, 1.0f };//{ R,G,B,�� }
	glColor4fv(col);
	//������̕`��
//	CText::DrawString("3D-RACE", 190, 430, 36, 36);
//	CText::DrawString("Push Enter Key", 200, 177, 16, 16);
	//2D�`��I��
	End2D();
}

CSceneTest::~CSceneTest()
{
	CTaskManager::Get()->Disabled();
	CTaskManager::Get()->Delete();
}
