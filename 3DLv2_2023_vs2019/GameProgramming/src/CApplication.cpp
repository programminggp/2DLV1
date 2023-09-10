#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CMatrix.h"
#include "CTransform.h"

#include "CCollisionManager.h"

#include "CBillBoard.h"
#include "CEnemy3.h"

#include "CCamera.h"

//�N���X��static�ϐ�
CTexture CApplication::mTexture;

CUi* CApplication::spUi = nullptr;
CApplication::~CApplication()
{
	delete spUi;	//�C���X�^���XUi�̍폜
}
CUi* CApplication::Ui()
{
	return spUi;
}

#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��
//���f���f�[�^�̎w��
#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl"
//�G�A���@���f��
#define MODEL_C5 "res\\c5.obj", "res\\c5.mtl"

//�w�i���f���f�[�^�̎w��
#define MODEL_BACKGROUND  "res\\sky.obj", "res\\sky.mtl"


//CTaskManager CApplication::mTaskManager;

//CTaskManager* CApplication::TaskManager()
//{
//	return &mTaskManager;
//}

//CCamera* CApplication::Camera()
//{
//	return &mCamera;
//}

CMatrix CApplication::mModelViewInverse;

const CMatrix& CApplication::ModelViewInverse()
{
	return mModelViewInverse;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	//29
	mActionCamera.Set(5.0f, -15.0f, 180.0f);

	mBackGround.Load("res\\sky.obj", "res\\sky.mtl");

//	mColliderMesh.Set(nullptr, nullptr, &mBackGround);

	mKnight.Load("res\\knight\\knight_low.x");
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:�ړ�
	mKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:�ҋ@
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:�_�~�[
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:�_�~�[
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:�_�~�[
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:�_�~�[
	mKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	mKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:�_�~�[
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:�_�~�[
	mKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:�_�E��

	//3D���f���t�@�C���̓ǂݍ���
	mModelX.Load(MODEL_FILE);
	//�L�����N�^�[�Ƀ��f����ݒ�
	mXPlayer.Init(&mModelX);
//	mXPlayer.Position(CVector(1, 1, 1));

	mFont.Load("FontG.png", 1, 4096 / 64);
	//�G�̏����ݒ�
	mXEnemy.Init(&mKnight);
	//�G�̔z�u
	mXEnemy.Position(CVector(7.0f, 0.0f, 0.0f));

	mXEnemy.ChangeAnimation(2, true, 200);

	mpPaladin = new CPaladin();
	mpPaladin->Position(CVector(-1.0f, 0.0f, 5.0f));

	//�A�j���[�V������؂�ւ��Ċm�F
	mpPaladin->ChangeAnimation(1, true, 60);
}

void CApplication::Update()
{
	//�L�����N�^�[�N���X�̍X�V
	mXPlayer.Update();
	//�G�̍X�V
	mXEnemy.Update();

	mpPaladin->Update();

	//�Փˏ���
	CCollisionManager::Instance()->Collision();

/*
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);
	//�J�����̐ݒ�
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
*/
	// �J�����ݒ�
	mActionCamera.Position(mXPlayer.Position() + CVector(0.0f, 2.0f, 0.0f));
	mActionCamera.Update();
	mActionCamera.Render();

	//���f���r���[�s��̎擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//�t�s��̎擾
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);

	/*
	//X���{��]
	if (mInput.Key('K')) {
		mMatrix = mMatrix * CMatrix().RotateX(1);
	}
	//Y���{��]
	if (mInput.Key('L')) {
		mMatrix = mMatrix * CMatrix().RotateY(1);
	}
	if (mInput.Key('I')) {
		mMatrix = mMatrix * CMatrix().RotateX(-1);
	}
	//Y���{��]
	if (mInput.Key('J')) {
		mMatrix = mMatrix * CMatrix().RotateY(-1);
	}
	//�s��ݒ�
	glMultMatrixf(mMatrix.M());
	*/

//	mBackGround.Render(mMatrix);
	//���f���`��
//	mModelX.Render();

	mXPlayer.Render();
	//�G�`��
	mXEnemy.Render();

	mpPaladin->Render();

	//�R���C�_�̕`��
	CCollisionManager::Instance()->Render();

	//2D�`��J�n
	CCamera::Start(0, 800, 0, 600);

	mFont.Draw(20, 20, 10, 12, "3D PROGRAMMING");

	CVector screen;
	//Enemy�̍��W���X�N���[�����W�֕ϊ����܂�
	if (CActionCamera::Instance()->WorldToScreen(&screen, mXEnemy.Position()))
	{
		//�ϊ���̍��W�ɕ�������o�͂���
		mFont.Draw(screen.X(), screen.Y(), 7, 14,"ENEMY");
	}

	//2D�̕`��I��
	CCamera::End();
}
