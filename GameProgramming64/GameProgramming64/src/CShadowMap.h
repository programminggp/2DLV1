#pragma once
#include "gl/freeglut.h"

class CShadowMap
{
	GLfloat mLightPos[3]; //�����̈ʒu
	GLfloat mShadowCol[4]; //�e�̐F
	int mTextureWidth; //�f�v�X�e�N�X�`���̕�
	int mTextureHeight; //�f�v�X�e�N�X�`���̍���
	GLuint mDepthTextureID; //�f�v�X�e�N�X�`��ID
	GLuint mFb; //�t���[���o�b�t�@���ʎq
	void (*mpRender)(); //Render�֐��̃|�C���^
	static bool sShadow;	//true�̎��́A�e�f�[�^�쐬�Ȃ̂ŃV�F�[�_�[���J�����g��Ȃ�
public:
	static bool Shadow();
	CShadowMap();
	~CShadowMap();
	//����������
	void Init();
	/* ����������
	void Init(int width, int height, void (*funcRender)(), float shadowCol[], float lightPos[])
	width:�f�v�X�e�N�X�`���̕�
	height:�f�v�X�e�N�X�`���̍���
	funcRender:�`��֐��̃|�C���^
	shadowCol:�e�̐F
	lightPos:�����̈ʒu
	*/
	void Init(int width, int height, void (*funcRender)(), float shadowCol[], float lightPos[]);
	//�`�揈��
	void Render();
};
