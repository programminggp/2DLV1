#include "CSceneGame.h"
//OpenGL
#include "glut.h"
//CVector�N���X�̃C���N���[�h
#include "CVector.h"
//CMatrix�N���X�̃C���N���[�h
#include "CMatrix.h"
//CTriangle�N���X�̃C���N���[�h
#include "CTriangle.h"
//���w�֐��̃C���N���[�h
#include <math.h>
//���f���N���X�̃C���N���[�h
#include "CModel.h"
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
//�^�X�N�}�l�[�W���̃C���N���[�h
#include "CTaskManager.h"
//�G�l�~�[�N���X�̃C���N���[�h
#include "CEnemy.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "CBillBoard.h"
#include "CEffect.h"
#include "CText.h"
#include "CRes.h"
#include "CC5.h"
#include "CObj.h"
#include "CKey.h"

//���f���N���X�̃C���X�^���X�쐬
CModel F14;
CModel Sky; //�w�i���f��
CModel F16;//�G�l�~�[���f��
CModel C5;

//�X�}�[�g�|�C���^�̐���
std::shared_ptr<CTexture> TextureExp(new CTexture());

CSceneGame::~CSceneGame() {
}

void CSceneGame::Init() {
	//�~�T�C��
	CRes::sMissileM.Load("missile.obj", "missile.mtl");
	//�����e�N�X�`���̓ǂݍ���
	TextureExp->Load("exp.tga");
	//���f���t�@�C���̓���
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	//1
	//�w�i���f���̐���
	Sky.Load("sky.obj", "sky.mtl");
	new CObj(&Sky, CVector(), CVector(), CVector(2.0f, 2.0f, 2.0f));

	//2
	//�v���C���[�̐ݒ�
	F14.Load("f14.obj", "f14.mtl");
	Player.mpModel = &F14;
	Player.mScale = CVector(0.1f, 0.1f, 0.1f);

	//6
	//C5�A���@�̐���
	C5.Load("c5.obj", "c5.mtl");
	new CC5(&C5, CVector(-100.0f, 10.0f, 300.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));

	//11
	//�G�@�̐���
	F16.Load("f16.obj", "f16.mtl");
	new CEnemy(&F16, CVector(-100.0f, 20.0f, 350.0f), CVector(0.0f, 180.0f, 0.0f), CVector(0.2f, 0.2f, 0.2f));
	new CEnemy(&F16, CVector(100.0f, 20.0f, 250.0f), CVector(0.0f, 180.0f, 0.0f), CVector(0.2f, 0.2f, 0.2f));

	//12
	//�A���@�ǉ�
	new CC5(&C5, CVector(50.0f, 50.0f, 380.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));
}


void CSceneGame::Update() {
	////static�ϐ��̍쐬
	static int frame = 0;//�t���[�����̃J�E���g
	frame++;

	//�^�X�N�}�l�[�W���̍X�V
	TaskManager.Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	CollisionManager.Collision();
	//�^�X�N���X�g�̍폜
	TaskManager.Delete();

	//�`�揈��

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����

	//5
	//�J�����̃p�����[�^��ݒ肷��
	e = CVector(-2.0f, 5.0f, -22.0f) * CMatrix().Scale(0.3f, 0.5f, 0.36f);
	c = CVector(0.0f, 4.0f, 0.0f);
	u = CVector(0.0f, 1.0f, 0.0f);
	
	if (CKey::Push('U'))
	{
		e = CVector(-2.0f, 5.0f, 22.0f) * Player.mMatrix;
	}
	else
	{
		e = CVector(-2.0f, 5.0f, -22.0f) * Player.mMatrix;
	}
	c = CVector(0.0f, 4.0f, 0.0f) * Player.mMatrix;
	u = CVector(0.0f, 1.0f, 0.0f) * Player.mMatrixRotate;
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	//�^�X�N�}�l�[�W���̕`��
	TaskManager.Render();

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	if (frame < 150) {
		//2D�`��
		CText::DrawString("MISSION START", 170, 400, 20, 20);
	}

	CText::DrawString("SPACE:SHOT M:MISSIL", 20, 50, 8, 12);
	CText::DrawString("W:DOWN S:UP A:LEFT D:RIGHT I:SPEEDUP K:SPEEDDOWN", 20, 20, 8, 12);

	//2D�`��I��
	End2D();

	return;

}

//2D�`��X�^�[�g
//Start2D(�����W, �E���W, �����W, ����W)
void CSceneGame::Start2D(float left, float right, float bottom, float top) {
	//���f���r���[�s��̑ޔ�
	glPushMatrix();
	//���f���r���[�s��̏�����
	glLoadIdentity();

	//���f���r���[�s�񂩂�
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޔ�
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//2D�`��̐ݒ�
	gluOrtho2D(left, right, bottom, top);
	//Depth�e�X�g�I�t
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
}

//2D�`��I��
void CSceneGame::End2D() {
	//�v���W�F�N�V�����s���߂�
	glPopMatrix();
	//���f���r���[���[�h�֐؂�ւ�
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�s���߂�
	glPopMatrix();
	//Depth�e�X�g�I��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

}

/*�}�b�v�ォ��̎��_*/
void CSceneGame::RenderMiniMap() {

	glPushMatrix();
	glViewport(600, 450, 200, 150); //��ʂ̕`��G���A�̎w��
	glLoadIdentity();
	gluLookAt(0, 100, 0, 0, 0, 0, 0, 0, 1);

	glDisable(GL_DEPTH_TEST);

	Sky.Render(CMatrix());
	//�^�X�N�}�l�[�W���̕`��
	TaskManager.Render();


	glPopMatrix();
	glViewport(0, 0, 800, 600); //��ʂ̕`��G���A�̎w��

	glEnable(GL_DEPTH_TEST);
}

