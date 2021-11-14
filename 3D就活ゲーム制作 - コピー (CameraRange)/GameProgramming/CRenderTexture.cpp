#include "glew.h"
#include "CRenderTexture.h"
#define FBOWIDTH 512	//�t���[���o�b�t�@�̕�
#define FBOHEIGHT 512	//�t���[���o�b�t�@�̍���
CRenderTexture::CRenderTexture()
: mColorBuffer(0)
, mRenderBuffer(0)
, mFrameBuffer(0)
{}
void CRenderTexture::Init()
{
	// �J���[�o�b�t�@�p�̃e�N�X�`����p�ӂ���
	glGenTextures(1, &mColorBuffer);
	glBindTexture(GL_TEXTURE_2D, mColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FBOWIDTH, FBOHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// �f�v�X�o�b�t�@�p�̃����_�[�o�b�t�@��p�ӂ���
	glGenRenderbuffers(1, &mRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, FBOWIDTH, FBOHEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// �t���[���o�b�t�@�I�u�W�F�N�g���쐬����
	glGenFramebuffers(1, &mFrameBuffer);
}

void CRenderTexture::Start()
{
	//�t���[���o�b�t�@�̃o�C���h
	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
	// �t���[���o�b�t�@�I�u�W�F�N�g�ɃJ���[�o�b�t�@�Ƃ��ăe�N�X�`������������
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorBuffer, 0);
	// �t���[���o�b�t�@�I�u�W�F�N�g�Ƀf�v�X�o�b�t�@�Ƃ��ă����_�[�o�b�t�@����������
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderBuffer);
	//�e�o�b�t�@�[���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CRenderTexture::End()
{
	// �t���[���o�b�t�@�I�u�W�F�N�g�̌�������������
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//�e�N�X�`����Ԃ�
GLuint CRenderTexture::GetTexture()
{
	return mColorBuffer;
}
