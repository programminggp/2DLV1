#ifndef CSHADOWMAP_H
#define CSHADOWMAP_H

#include "CVector.h"
#include "glfw/glfw3.h"

class CShadowMap
{
	GLint	mTextureWidth, mTextureHeight; //Depth�e�N�X�`���̕��ƍ���
	GLuint	mDepthTextureID; //Depth�e�N�X�`����ID
	GLint	viewport[4]; //�r���[�|�[�g�̕ۑ��p
	CMatrix	modelview; //���f���r���[�ϊ��s��̕ۑ��p
	CMatrix	projection; //�����ϊ��s��̕ۑ��p
public:
	~CShadowMap();
	//Init(Depth�e�N�X�`���̕�,Depth�e�N�X�`���̍���)
	void Init(GLuint width, GLuint height);
	//Step1Init(���C�g�̈ʒu)
	void Step1Init(const CVector &lightPosition);
	//�e�̕`��J�n
	void Step2Begin();
	//�e�̕`��I��
	void Step3End();
};

#endif
