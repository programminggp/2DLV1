#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "CVector3.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CTask.h"

class CTriangle : public CTask {
private: 
	enum  E_TEXVER
	{
		E_TOP,
		E_BOTTOM,
		E_LEFT,
		E_RIGHT,
		E_TEX_ARRAY
	};
	float mSaveInitTexVer[E_TEX_ARRAY];//�e�N�X�`���̃T�C�Y�ۑ� ���߂̒l
	float mSaveTexVer[E_TEX_ARRAY];//�e�N�X�`���̃T�C�Y�ۑ� ���݂̒l
	bool mFlagSaveTex;//�e�N�X�`�����Z�[�u���ꂽ�����f
public:
	/*���_��*/
	enum E_VER{
		E_LEFT_TOP,//����
		E_LEFT_BOTTOM,//����
		E_RIGHT_BOTTOM,//�E��
		E_VER_ARRAY,//�z��
	};

	CVector3 mVertex[E_VER_ARRAY];	//���_�̍��W�@3���_��
	CVector3 mNormal;		//�ʂ̖@��
	CTexture *mpTexture;	//�e�N�X�`��
	bool mEnabled;			//�l�p�`���ݒ肳��Ă��邩�̃t���O
	float mUv[4][2];		//�e�N�X�`���}�b�s���O
	float r,g,b,a;			//�F�f�[�^
	float diffuse[4];


	//���_�f�[�^�̐ݒ�
	void SetVertex(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2);

	//�J���[��ݒ�
	void SetDiffuse(float cr, float cg, float cb, float ca);

	/*�@���ݒ�*/
	void SetNormal(float x, float y, float z);
	

	//�e�N�X�`���ƃe�N�X�`���}�b�s���O�̐ݒ�
	void SetUv(CTexture *texture, int left, int top, int right, int bottom);
	//���[�e�[�V����������
	void SetUvRot();

	CTriangle();

	/*�`�揈��*/
	void Render();	

	/*
	�t�F�[�h�֐� speed = �t�F�[�h�̑���
	a = ALPHA
	*/
	void Fade(float speed, float alaha);
	/*
	�t�F�[�h�֐� speed = �t�F�[�h�̑���
	a = ALPHA
	*/
	void FadeOut(float speed, float alaha);


	/*�e�N�X�`�����X�N���[���֐�*/
	void TexSideScroll(float speed);
	/*�e�N�X�`���c�X�N���[���֐�*/
	void TexVerticalScroll(float speed);
};

#endif
