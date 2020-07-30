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
//
#include "CCollisionManager.h"
//
#include "CCamera.h"
//�r���{�[�h�N���X�̃C���N���[�h
#include "CBillBoard.h"
#include "CEffect.h"
//��R��n
#include "CAirBase.h"
//
#include "CText.h"
//
#include "CRes.h"
//
#include "CC5.h"
//
#include "CObj.h"

//���f���N���X�̃C���X�^���X�쐬
CModel Model;
CModel BackGround; //�w�i���f��
CModel ModelEnemy;//�G�l�~�[���f��
CModel ModelAirBase;//��R��n���f��

//�X�}�[�g�|�C���^�̐���
std::shared_ptr<CTexture> TextureExp(new CTexture());

CSceneGame::~CSceneGame() {
//	delete[] mpEnemyPoint;
}

void CSceneGame::Init() {
	//�~�T�C��
	CRes::sMissileM.Load("missile.obj", "missile.mtl");
	//C5�A���@
	CRes::sC5.Load("c5.obj", "c5.mtl");
	//���f���t�@�C���̓���
	Model.Load("f14.obj", "f14.mtl");
	BackGround.Load("sky.obj", "sky.mtl");

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	//�|�C���g�̐ݒ�
	//CEnemy::mPointSize = 3;//�|�C���g���̐ݒ�
	//mpEnemyPoint = new CPoint[CEnemy::mPointSize];
	//mpEnemyPoint[0].Set(CVector(35.0f, 25.0f, 100.0f), 10.0f);
	//mpEnemyPoint[1].Set(CVector(35.0f, 5.0f, 0.0f), 10.0f);
	//mpEnemyPoint[2].Set(CVector(-35.0f, 45.0f, 50.0f), 10.0f);
	//CEnemy::mPoint = mpEnemyPoint;


	//�L�����N�^�̐ݒ�
	Player.mpModel = &Model;
	//�X�P�[����0.2�{��ύX
	Player.mScale = CVector(0.1f, 0.1f, 0.1f);
	//�ʒu(0.0, 0.0, 55.0)�ɂ���
//	Player.mPosition = CVector(-20.0f, 30.0f, -100.0f);
	Player.mPosition = CVector(-20.0f, 30.0f, 400.0f);
	Player.mRotation.mY = 180.0f;

	//�G�l�~�[���f���̓���
//	ModelEnemy.Load("f16.obj", "f16.mtl");

	//�G�@�̐���
	//�����e�N�X�`���̓ǂݍ���
	TextureExp->Load("exp.tga");

	//��R��n���f���̓ǂݍ���
//	ModelAirBase.Load("airbase.obj", "airbase.mtl");
	//��R��n�N���X�̃C���X�^���X�𐶐�
//	mpAirBase = new CAirBase(&ModelAirBase, CVector(0.0f, 0.0f, 180.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CObj(&BackGround, CVector(), CVector(), CVector(2.0f, 2.0f, 2.0f));

	CC5 *cc5;
	cc5 = new CC5(&CRes::sC5, CVector(-100.0f, 10.0f, 400.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));
	cc5 = new CC5(&CRes::sC5, CVector(50.0f, 50.0f, 450.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));

}


void CSceneGame::Update() {
	//static�ϐ��̍쐬
	//static int degree = 0;//��]�p�x�̍쐬
	//degree++;//�p�x��1���Z

	////static�ϐ��̍쐬
	static int frame = 0;//�t���[�����̃J�E���g
	frame++;//�t���[������1���Z
	//if (frame < 1000 && frame % 150 == 0) {
	//	//�G�@�̐���
	//	new CEnemy(&ModelEnemy, CVector(-10.0f, 7.0f, 200.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));
	//}

	//�^�X�N�}�l�[�W���̍X�V
	TaskManager.Update();

	//�`�揈��

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(-2.0f, 5.0f, -22.0f) * Player.mMatrix;
	//�����_�����߂�
	c = CVector(0.0f, 4.0f, 0.0f) * Player.mMatrix;
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f) * Player.mMatrixRotate;
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	//�R���W�����}�l�[�W���̏Փˏ���
	CollisionManager.Collision();

	//�^�X�N���X�g�̍폜
	TaskManager.Delete();
	//�^�X�N�}�l�[�W���̕`��
	TaskManager.Render();
	//�R���C�_�̕`��
//	CollisionManager.Render();

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	if (frame < 150) {
		//2D�`��
		CText::DrawString("MISSION START", 170, 400, 20, 20);
	}

//	CText::DrawString("PLAYER DAMAGE ", 20, 50, 10, 12);
	CText::DrawString("SPACE:SHOT", 20, 50, 8, 12);
	CText::DrawString("W:DOWN S:UP A:LEFT D:RIGHT I:SPEEDUP K:SPEEDDOWN", 20, 20, 8, 12);

	//2D�`��I��
	End2D();

	//�~�j�}�b�v�`��
//	RenderMiniMap();

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

	BackGround.Render(CMatrix());
	//�^�X�N�}�l�[�W���̕`��
	TaskManager.Render();


	glPopMatrix();
	glViewport(0, 0, 800, 600); //��ʂ̕`��G���A�̎w��

	glEnable(GL_DEPTH_TEST);
}

