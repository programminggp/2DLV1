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

//���f���N���X�̃C���X�^���X�쐬
CModel Model;
CModel BackGround; //�w�i���f��
CModel ModelEnemy;//�G�l�~�[���f��
//30
CModel ModelAirBase;//��R��n���f��

//�X�}�[�g�|�C���^�̐���
//std::shared_ptr<CTexture> TextureExp(new CTexture());
CMaterial MaterialExp;

CSceneGame::~CSceneGame() {
	delete[] CEnemy::mPoint;
}


void CSceneGame::Init() {
	//
	CRes::mMissileM.Load("missile.obj", "missile.mtl");

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
//	CText::mFont.Load("Font.tga");
//	CText::mFont.SetRowCol(8, 16);

	//�|�C���g�̐ݒ�
	CEnemy::mPointSize = 3;//�|�C���g���̐ݒ�
	CEnemy::mPoint = new CPoint[CEnemy::mPointSize];
	CEnemy::mPoint[0].Set(CVector(35.0f, 25.0f, 100.0f), 10.0f);
	CEnemy::mPoint[1].Set(CVector(35.0f, 5.0f, 0.0f), 10.0f);
	CEnemy::mPoint[2].Set(CVector(-35.0f, 45.0f, 50.0f), 10.0f);

	CMatrix matrix;
	//���s�ړ��s��̍쐬
	matrix.Translate(1.0f, 2.0f, 3.0f);
	matrix.Print();
	//���f���t�@�C���̓���
	Model.Load("f14.obj", "f14.mtl");
	BackGround.Load("sky.obj", "sky.mtl");

	//�L�����N�^�̐ݒ�
	Player.mpModel = &Model;
	//�X�P�[����0.2�{��ύX
//	Player.mScale = CVector(0.2f, 0.2f, 0.2f);
	Player.mScale = CVector(1.0f, 1.0f, 1.0f);
	//�ʒu(0.0, 0.0, 55.0)�ɂ���
	Player.mPosition = CVector(-19.5f, 1.0f, -55.0f);

	//�G�l�~�[���f���̓���
	ModelEnemy.Load("f16.obj", "f16.mtl");

	//�G�@�̐���
	//�����e�N�X�`���̓ǂݍ���
	//TextureExp->Load("exp.tga");
	MaterialExp.SetTexture("exp.tga");

	//?
//	mMap.mpModel = &BackGround;
//	mMap.mScale = CVector(2.0f, 2.0f, 2.0f);
//	mMap.SetTriangleCollider();

	//?
	//36
	//��R��n���f���̓ǂݍ���
	ModelAirBase.Load("airbase.obj", "airbase.mtl");
	//��R��n�N���X�̃C���X�^���X�𐶐�
	mpAirBase = new CAirBase(&ModelAirBase, CVector(0.0f, 0.0f, 180.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
}


void CSceneGame::Update() {
	//static�ϐ��̍쐬
	static int degree = 0;//��]�p�x�̍쐬
	degree++;//�p�x��1���Z

	//static�ϐ��̍쐬
	static int frame = 0;//�t���[�����̃J�E���g
	frame++;//�t���[������1���Z
	if (frame < 1000 && frame % 150 == 0) {
		//�G�@�̐���
		new CEnemy(&ModelEnemy, CVector(-10.0f, 7.0f, 200.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));
	}

	//�^�X�N�}�l�[�W���̍X�V
	TaskManager.Update();

	//�`�揈��

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
//	e = CVector(-2.0f, 10.0f, -30.0f) * Player.mMatrix;
	e = CVector(-2.0f, 10.0f, -30.0f) + Player.mPosition;
	//�����_�����߂�
	c = Player.mPosition;
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f) * Player.mMatrixRotate;
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	//�R���W�����}�l�[�W���̏Փˏ���
	CollisionManager.Collision();

	BackGround.Render(CMatrix());

	//�^�X�N���X�g�̍폜
	TaskManager.Delete();
	//�^�X�N�}�l�[�W���̕`��
	TaskManager.Render();
	//�R���C�_�̕`��
	CollisionManager.Render();

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	if (frame < 150) {
		//2D�`��
		CText::DrawString("MISSION START", 170, 400, 20, 20);
	}

	CText::DrawString("PLAYER DAMAGE ", 20, 50, 10, 12);
	CText::DrawString("AIRBASE DAMAGE", 20, 20, 10, 12);
	//char buf[10];
	//sprintf(buf, "%d", mpAirBase->mDamage);
	//CText::DrawString(buf, 320, 20, 10, 12);

	//2D�`��I��
	End2D();

	//�~�j�}�b�v�`��
	RenderMiniMap();

	return;

/*
	CMatrix matrix;//�s��쐬

	//���_1����_2����_3,�@���f�[�^�̍쐬
	CVector v0, v1, v2, n;

	//�@����������Őݒ肷��
	n.mX = 0.0f; n.mY = 1.0f; n.mZ = 0.0f;

	//���_1�̍��W��ݒ肷��
	v0.mX = 0.0f; v0.mY = 0.0f; v0.mZ = 0.5f;
	//���_2�̍��W��ݒ肷��
	v1.mX = 1.0f; v1.mY = 0.0f; v1.mZ = 0.0f;
	//���_3�̍��W��ݒ肷��
	v2.mX = 0.0f; v2.mY = 0.0f; v2.mZ = -0.5f;

	//���_�̐ݒ�
	//gluLookAt(���_X, ���_Y, ���_Z, ���SX, ���SY, ���SZ, ���X, ���Y, ���Z)
	gluLookAt(1.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//�`��J�n
	//glBegin(�`)
	//GL_TRIANGLES�F�O�p�`
	glBegin(GL_TRIANGLES);

	//Y�����S�Ɋp�x������]������s���ݒ�
	matrix.RotateY(degree);
	//�@���ƒ��_����]������
	//n = n.Multi(matrix);
	v0 = v0.Multi(matrix);
	v1 = v1.Multi(matrix);
	v2 = v2.Multi(matrix);

	//�@���i�ʂ̌����j�̐ݒ�
	//glNormal3f(X���W, Y���W, Z���W)
	glNormal3f(n.mX, n.mY, n.mZ);
	//���_���W�̐ݒ�
	//glVertex3f(X���W, Y���W, Z���W)
	glVertex3f(v0.mX, v0.mY, v0.mZ);
	glVertex3f(v1.mX, v1.mY, v1.mZ);
	glVertex3f(v2.mX, v2.mY, v2.mZ);

	//�@���ƒ��_�̐ݒ�
	n.Set(0.0f, 0.0f, 1.0f);
	v0.Set(0.5f, 0.0f, 0.0f);
	v1.Set(0.0f, 1.0f, 0.0f);
	v2.Set(-0.5f, 0.0f, 0.0f);

	matrix.RotateZ(degree);
	//�@���ƒ��_����]������
	n = n.Multi(matrix);
	v0 = v0.Multi(matrix);
	v1 = v1.Multi(matrix);
	v2 = v2.Multi(matrix);

	//�O�p�`2�̕`��
	glNormal3f(n.mX, n.mY, n.mZ);
	glVertex3f(v0.mX, v0.mY, v0.mZ);
	glVertex3f(v1.mX, v1.mY, v1.mZ);
	glVertex3f(v2.mX, v2.mY, v2.mZ);

	//�@���ƒ��_�̐ݒ�
	n.Set(1.0f, 0.0f, 0.0f);
	v0.Set(0.0f, 0.5f, 0.0f);
	v1.Set(0.0f, 0.0f, 1.0f);
	v2.Set(0.0f, -0.5f, 0.0f);

	matrix.RotateX(degree);
	//�@���ƒ��_����]������
	n = n.Multi(matrix);
	v0 = v0.Multi(matrix);
	v1 = v1.Multi(matrix);
	v2 = v2.Multi(matrix);

	//�O�p�`3�̕`��
	glNormal3f(n.mX, n.mY, n.mZ);
	glVertex3f(v0.mX, v0.mY, v0.mZ);
	glVertex3f(v1.mX, v1.mY, v1.mZ);
	glVertex3f(v2.mX, v2.mY, v2.mZ);

	//�`��I��
	glEnd();

	//�O�p�`�N���X�̃C���X�^���X�쐬
	CTriangle t0;
	//�@���ƒ��_�̐ݒ�
	t0.SetVertex(CVector(0.0f, 0.0f, 0.5f), CVector(1.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, -0.5f));
	t0.SetNormal(CVector(0.0f, 1.0f, 0.0f));
	//�O�p�`�̕`��
//	t0.Render(matrix.Translate(degree*0.01, 0.0f, 0.0f));
//	t0.Render(matrix.Scale(sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5, sinf(degree*0.01) +1.5));
	//��]�s��ƈړ��s����|���č����s������
	matrix = matrix.RotateY(degree) * matrix.Translate(2.0f, 0.0f, 0.0f);
	t0.Render(matrix);

	CTriangle t1;
	//�@���ƒ��_�̐ݒ�
	t1.SetVertex(CVector(0.5f, 0.0f, 0.0f), CVector(0.0f, 1.0f, 0.0f), CVector(-0.5f, 0.0f, 0.0f));
	t1.SetNormal(CVector(0.0f, 0.0f, 1.0f));
	//�O�p�`�̕`��
//	t1.Render();
	matrix.Translate(0.0f, degree*0.01, 0.0f);
//	t1.Render(matrix.RotateZ(degree));
//	t1.Render(matrix);
//	t1.Render(matrix.Scale(sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5));
	matrix = matrix.RotateZ(degree) * matrix.Translate(0.0f, 2.0f, 0.0f);
	t1.Render(matrix);

	CTriangle t2;
	//�@���ƒ��_�̐ݒ�
	t2.SetVertex(CVector(0.0f, 0.5f, 0.0f), CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, -0.5f, 0.0f));
	t2.SetNormal(CVector(1.0f, 0.0f, 0.0f));
	//�O�p�`�̕`��
//	t2.Render();
//	matrix.Translate(0.0f, 0.0f, degree*0.01);
//	t2.Render(matrix.RotateX(degree));
//	t2.Render(matrix);
//	t2.Render(matrix.Scale(sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5));
	matrix = matrix.RotateX(degree) * matrix.Translate(0.0f, 0.0f, 2.0f);
	t2.Render(matrix);
*/

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

