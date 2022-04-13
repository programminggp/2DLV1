//�V�[���Q�[���N���X�̃C���N���[�h
#include "CSceneGame.h"
//OpenGL
#include"glut.h"
//�x�N�g���N���X�̃C���N���[�h
#include"CVector.h"
//�O�p�`�N���X�̃C���N���[�h
#include"CTriangle.h"
//�L�[�N���X�̃C���N���[�h
#include"CKey.h"
//�}�g���b�N�X�N���X�̃C���N���[�h
#include"CMatrix.h"
//�g�����X�t�H�[���N���X�̃C���N���[�h
#include"CTransform.h"
//�L�����N�^�N���X�̃C���N���[�h
#include"CCharacter.h"
//�^�X�N�}�l�[�W���N���X�̃C���N���[�h
#include"CTaskManager.h"
//�G�̃N���X�̃C���N���[�h
#include"CEnemy.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include"CCollisionManager.h"
//�r���{�[�h�N���X�̃C���N���[�h
#include"CBillBoard.h"
//�J�����N���X�̃C���N���[�h
#include"CCamera.h"
//�O�p�R���C�_�N���X�̃C���N���[�h
#include"CColliderTriangle.h"
//���f���f�[�^�̎w��
#define MODEL_OBJ "res\\f14.obj","res\\f14.mtl"
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"
//�J�����̎��_�̕ϐ�
CVector mEye;

//�}�g���b�N�X�̕ϐ�
CMatrix matrix;


void CSceneGame::Init() {
	mBackGroundMatrix.Translate(0.0f, 0.0f, -500.0f);
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//���f���t�@�C���̓���
	mModel.Load(MODEL_OBJ);
	//�w�i���f���t�@�C���̓���
	mBackGround.Load(MODEL_BACKGROUND);
	//�G�̃��f���̓ǂݍ���
	mModelC5.Load("res\\C5.obj","res\\C5.mtl");
	//�}�g���b�N�X�̕`��ϐ�
	matrix.Print();
	//�v���C���[�̃��f���|�C���^
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f) * mBackGroundMatrix);
	mPlayer.Rotation(CVector(0.0f, 180.0f,0.0f));
	//�G�@�̃C���X�^���X�쐬
	new CEnemy(&mModelC5,CVector(0.0f, 10.0f, -100.0f) * mBackGroundMatrix,
		CVector(),CVector(0.1f,0.1f,0.1f));
	new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f) * mBackGroundMatrix,
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	//�r���{�[�h�̐���
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);

	//�w�i���f������O�p�R���C�_�𐶐�
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &mBackGround);

}

void CSceneGame::Update() {
	//�^�X�N�}�l�[�W���̍X�V
	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
//�폜	CCollisionManager::Get()->Collision();
	CTaskManager::Get()->TaskCollision();

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_,�����_,�����
	//���_�����߂�
	e = mPlayer.Position() + CVector(-0.2f,1.0f,-3.0f) * mPlayer.MatirixRotate();
	//�����_�����߂�
	c = mPlayer.Position();
	//����������߂�
	u = CVector(0.0f,1.0f,0.0f) * mPlayer.MatirixRotate();
	//�J�����̐ݒ�
	//gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();
	
	

	
	
	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();
	//�^�X�N�}�l�[�W���̕`��	
	CTaskManager::Get()->Render();
	//�w�i���f���̕`��
	mBackGround.Render(mBackGroundMatrix);
	//�R���W�����}�l�[�W���̃R���C�_�`��
	CCollisionManager::Get()->Render();
}
	


