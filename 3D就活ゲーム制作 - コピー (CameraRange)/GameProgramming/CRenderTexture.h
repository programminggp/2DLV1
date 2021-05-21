#ifndef CRENDERTEXTURE_H
#define CRENDERTEXTURE_H
#include "glfw/glfw3.h"

//�����_�[�e�N�X�`���N���X
class CRenderTexture
{
private:
	GLuint mColorBuffer;	//�J���[�o�b�t�@
	GLuint mRenderBuffer;	//�����_�[�o�b�t�@
	GLuint mFrameBuffer;	//�t���[���o�b�t�@
public:
	//�R���X�g���N�^
	CRenderTexture();
	//�����ݒ菈��
	void Init();
	//�����_�����O�J�n
	void Start();
	//�����_�����O�I��
	void End();
	//�e�N�X�`���̎擾
	GLuint GetColorBuffer();
};

#endif
