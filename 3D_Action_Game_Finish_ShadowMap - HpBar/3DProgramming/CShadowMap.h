#ifndef CSHADOWMAP_H
#define CSHADOWMAP_H

#include "CVector3.h"
#include "glew.h"

class CShadowMap {
	/*
	** �e�N�X�`���I�u�W�F�N�g�E�t���[���o�b�t�@�I�u�W�F�N�g
	*/
	GLuint mTex, mFb;
	GLint viewport[4];       /* �r���[�|�[�g�̕ۑ��p�@�@�@�@ */
	GLdouble modelview[16];  /* ���f���r���[�ϊ��s��̕ۑ��p */
	GLdouble projection[16]; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */

public:
	CVector3 mLightPosition;	//�����ʒu
	CVector3 mLightCenter;		//������
	float mDepthTextureWidth;	//�[�x�e�N�X�`���̕�
	float mDepthTextureHeight;	//�[�x�e�N�X�`���̍���
	float mFov;					//�[�x�e�N�X�`���쐬���̓��e��p
	void SetLight(const CVector3& pos, const CVector3& center, float fov);
	void SetTextureSize(float width, float height);
	void Init(float width, float height);
	void RenderInit();
	void RenderBegin();
	void RenderEnd();
};

#endif
