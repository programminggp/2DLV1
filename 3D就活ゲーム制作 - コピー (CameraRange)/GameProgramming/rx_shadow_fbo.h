#pragma once
/*!
  @file rx_shadow_gl.h

  @brief �V���h�E�}�b�v(GLSL����,FBO�g�p��)
		 �Q�l : http://www.paulsprojects.net/tutorials/smt/smt.html

  @author Makoto Fujisawa
  @date 2013-
*/
// FILE --rx_shadowmap--

#ifndef _RX_SHADOWMAP_GL_H_
#define _RX_SHADOWMAP_GL_H_


//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------

// OpenGL
#include <glew.h>
//#include <glut.h>

#include <iostream>

//#include "rx_utility.h"
#include "CVector.h"

using namespace std;

#define Vec3 CVector

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
struct rxFrustum
{
	double Near;
	double Far;
	double FOV;	// deg
	double W, H;
	Vec3 Origin;
	Vec3 LookAt;
	Vec3 Up;
};

const GLfloat RX_LIGHT_DIM[4] = { 0.2f, 0.2f, 0.2f, 0.2f };
const GLfloat RX_LIGHT_WHITE[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat RX_LIGHT_BLACK[4] = { 0.0f, 0.0f, 0.0f, 0.0f };


//-----------------------------------------------------------------------------
// �V���h�E�}�b�s���O�N���X
//-----------------------------------------------------------------------------
class rxShadowMap
{
	GLuint m_iFBODepth;			//!< �������猩���Ƃ��̃f�v�X���i�[����Framebuffer object
	GLuint m_iTexShadowMap;		//!< �V���h�E�}�b�v�e�N�X�`��
	int m_iShadowMapSize[2];	//!< �V���h�E�}�b�v�e�N�X�`���̃T�C�Y

public:
	//! �f�t�H���g�R���X�g���N�^
	rxShadowMap()
	{
		m_iTexShadowMap = 0;
		m_iShadowMapSize[0] = m_iShadowMapSize[1] = 1024;
	}

	//! �f�X�g���N�^
	~rxShadowMap() {}

	/*!
	 * 4x4�s�񓯎m�̂����Z
	 * @param[out] m ���ʍs��
	 * @param[in] a,b 4x4�s��
	 */
	inline void MulMat(float m[16], const float a[16], const float b[16])
	{
		m[0] = a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12] * b[3];
		m[1] = a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13] * b[3];
		m[2] = a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14] * b[3];
		m[3] = a[3] * b[0] + a[7] * b[1] + a[11] * b[2] + a[15] * b[3];
		m[4] = a[0] * b[4] + a[4] * b[5] + a[8] * b[6] + a[12] * b[7];
		m[5] = a[1] * b[4] + a[5] * b[5] + a[9] * b[6] + a[13] * b[7];
		m[6] = a[2] * b[4] + a[6] * b[5] + a[10] * b[6] + a[14] * b[7];
		m[7] = a[3] * b[4] + a[7] * b[5] + a[11] * b[6] + a[15] * b[7];
		m[8] = a[0] * b[8] + a[4] * b[9] + a[8] * b[10] + a[12] * b[11];
		m[9] = a[1] * b[8] + a[5] * b[9] + a[9] * b[10] + a[13] * b[11];
		m[10] = a[2] * b[8] + a[6] * b[9] + a[10] * b[10] + a[14] * b[11];
		m[11] = a[3] * b[8] + a[7] * b[9] + a[11] * b[10] + a[15] * b[11];
		m[12] = a[0] * b[12] + a[4] * b[13] + a[8] * b[14] + a[12] * b[15];
		m[13] = a[1] * b[12] + a[5] * b[13] + a[9] * b[14] + a[13] * b[15];
		m[14] = a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15];
		m[15] = a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15];
	}



	/*!
	 * �V���h�E�}�b�v�p�e�N�X�`���̏�����
	 * @param[in] w,h  �V���h�E�}�b�v�̉𑜓x
	 */
	int InitShadow(int w_ = 512, int h_ = 512)
	{
		// 
		glewInit();
		if (!glewIsSupported("GL_ARB_depth_texture "
			"GL_ARB_shadow "
		)) {
			cout << "ERROR: Support for necessary OpenGL extensions missing." << endl;
			return 0;
		}

		m_iShadowMapSize[0] = w_;
		m_iShadowMapSize[1] = h_;

		// �f�v�X�}�b�v�̏������ƗL����
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);

		// �V���h�E�}�b�v�e�N�X�`���̐���
		glGenTextures(1, &m_iTexShadowMap);
		glBindTexture(GL_TEXTURE_2D, m_iTexShadowMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_iShadowMapSize[0], m_iShadowMapSize[1], 0,
			GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		GLfloat border_color[4] = { 1, 1, 1, 1 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

		glBindTexture(GL_TEXTURE_2D, 0);

		// FBO�쐬
		glGenFramebuffersEXT(1, &m_iFBODepth);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_iFBODepth);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		// �V���h�E�}�b�v�e�N�X�`����FBO�ɐڑ�
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_iTexShadowMap, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return 1;
	}

	/*!
	 * �V���h�E�}�b�v(�f�v�X�e�N�X�`��)�̍쐬
	 * @param[in] light ����
	 * @param[in] fpDraw �`��֐��|�C���^
	 */
	void RenderSceneWithShadow(rxFrustum& light, void (*fpDraw)(void*), void* func_obj)
	{
		float light_proj[16], camera_proj[16];
		float light_modelview[16], camera_modelview[16];


		//
		// ���݂̎��_�s��C�����s����擾 or �쐬
		//
		glMatrixMode(GL_PROJECTION);

		// ���_�v���W�F�N�V�����s��̎擾
		glGetFloatv(GL_PROJECTION_MATRIX, camera_proj);
		glPushMatrix();	// ���̃v���W�F�N�V�����s���ޔ������Ă���

		// �����v���W�F�N�V�����s��̐����Ǝ擾
		glLoadIdentity();
		gluPerspective(light.FOV, (double)light.W / (double)light.H, light.Near, light.Far);
		glGetFloatv(GL_PROJECTION_MATRIX, light_proj);

		glMatrixMode(GL_MODELVIEW);

		// ���_���f���r���[�s��̎擾
		glGetFloatv(GL_MODELVIEW_MATRIX, camera_modelview);
		glPushMatrix();	// ���̃��f���r���[�s���ޔ������Ă���

		// �������f���r���[�s��̐����Ǝ擾
		glLoadIdentity();
		gluLookAt(light.Origin.mX, light.Origin.mY, light.Origin.mZ,
			light.LookAt.mX, light.LookAt.mY, light.LookAt.mZ,
			light.Up.mX, light.Up.mY, light.Up.mZ);
		glGetFloatv(GL_MODELVIEW_MATRIX, light_modelview);

		// ���̃r���[�|�[�g������Ŗ߂����߂Ɋm��
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);


		//
		// �������烌���_�����O���ăV���h�E�}�b�v�𐶐�
		//
		glBindFramebuffer(GL_FRAMEBUFFER, m_iFBODepth);	// FBO�Ƀ����_�����O

		// �J���[�C�f�v�X�o�b�t�@�̃N���A
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// �V���h�E�}�b�v�Ɠ����T�C�Y�̃r���[�|�[�g��ݒ�
		glViewport(0, 0, m_iShadowMapSize[0], m_iShadowMapSize[1]);

		// ���������_�Ƃ��Đݒ�
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(light_proj);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(light_modelview);

		// �����ɑ΂��ė��̖ʂɉe���������Ȃ��ꍇ��glCullFace(GL_FRONT)�ŕ\�ʂ��J�����O����悤�ɐݒ�
		glCullFace(GL_FRONT);
		//glCullFace(GL_BACK);

		// �������̂��߂Ƀt���b�g�V�F�[�f�B���O��ݒ�
		glShadeModel(GL_FLAT);

		// �f�v�X�l�ȊO�̐F�̃����_�����O�𖳌���
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		glPolygonOffset(1.1f, 4.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);

		// �V�[���`��
		fpDraw(func_obj);

		glDisable(GL_POLYGON_OFFSET_FILL);

		// �f�v�X�o�b�t�@���e�N�X�`���ɓ]��
		//glBindTexture(GL_TEXTURE_2D, m_iTexShadowMap);
		//glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_iShadowMapSize[0], m_iShadowMapSize[1]);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glCullFace(GL_BACK);
		glShadeModel(GL_SMOOTH);

		// �����ɂ����F�̃����_�����O��L���ɂ���
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		// ���̃r���[�|�[�g�s��ɖ߂�
		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

		// �ޔ������Ă��������_�s������ɖ߂�
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();


		//
		// �J�������猩���Ƃ��̃V�[���`��F�e�̈�
		// 
		glClear(GL_DEPTH_BUFFER_BIT);

		// �e�G���A�p�̈Â����C�g�̐ݒ�(�Ȃ�ׂ����̌����ݒ�Əd�����Ȃ��悤��LIGHT7���g�p)
		float light_pos[4] = { light.Origin.mX, light.Origin.mY, light.Origin.mZ, 1.0 };
		glLightfv(GL_LIGHT7, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT7, GL_AMBIENT, RX_LIGHT_DIM);
		glLightfv(GL_LIGHT7, GL_DIFFUSE, RX_LIGHT_DIM);
		glLightfv(GL_LIGHT7, GL_SPECULAR, RX_LIGHT_BLACK);
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT7);
		glEnable(GL_LIGHTING);

		// �`��
		fpDraw(func_obj);

		glDisable(GL_LIGHT7);


		//
		// �J�������猩���Ƃ��̃V�[���`��F�����̈�
		// 
		glEnable(GL_LIGHT0);

		// �e�N�X�`���s��p�̃o�C�A�X�s��		
		const float bias[16] = { 0.5, 0.0, 0.0, 0.0,
								 0.0, 0.5, 0.0, 0.0,
								 0.0, 0.0, 0.5, 0.0,
								 0.5, 0.5, 0.5, 1.0 };

		// �e�N�X�`���s��(���_��Ԃ��烉�C�g��Ԃւ̕ϊ��s��)�̌v�Z
		float tex_mat[16], tmp[16];
		MulMat(tmp, bias, light_proj);
		MulMat(tex_mat, tmp, light_modelview);

		// �e�N�X�`�����W�n�̐ݒ�
		float t[4];
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		t[0] = tex_mat[0]; t[1] = tex_mat[4]; t[2] = tex_mat[8]; t[3] = tex_mat[12];
		glTexGenfv(GL_S, GL_EYE_PLANE, t);
		glEnable(GL_TEXTURE_GEN_S);

		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		t[0] = tex_mat[1]; t[1] = tex_mat[5]; t[2] = tex_mat[9]; t[3] = tex_mat[13];
		glTexGenfv(GL_T, GL_EYE_PLANE, t);
		glEnable(GL_TEXTURE_GEN_T);

		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		t[0] = tex_mat[2]; t[1] = tex_mat[6]; t[2] = tex_mat[10]; t[3] = tex_mat[14];
		glTexGenfv(GL_R, GL_EYE_PLANE, t);
		glEnable(GL_TEXTURE_GEN_R);

		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		t[0] = tex_mat[3]; t[1] = tex_mat[7]; t[2] = tex_mat[11]; t[3] = tex_mat[15];
		glTexGenfv(GL_Q, GL_EYE_PLANE, t);
		glEnable(GL_TEXTURE_GEN_Q);


		// �V���h�E�}�b�v�e�N�X�`��
		glBindTexture(GL_TEXTURE_2D, m_iTexShadowMap);
		glEnable(GL_TEXTURE_2D);

		// �e�N�X�`��R���W�ƃe�N�X�`�����r����悤�ɐݒ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

		// R <= �e�N�X�`���̒l �Ȃ��true(����)�ɂ���
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

		// ��r���ʂ͑S�̂̐F�Ƃ��Ĕ��f(�A���t�@�l����(GL_ALPHA)�ł��悢)
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

		// ���l�̔�r�֐���ݒ�(��2�����͂������l)
		glAlphaFunc(GL_GEQUAL, 0.5f);
		glEnable(GL_ALPHA_TEST);

		// �������������̐}�`�ɏd�˂ď������悤�Ƀf�v�X��r�֐���ݒ�
		glDepthFunc(GL_LEQUAL);

		fpDraw(func_obj);

		glDisable(GL_TEXTURE_2D);

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_GEN_Q);

		glDisable(GL_LIGHTING);
		glDisable(GL_ALPHA_TEST);
	}

	void RenderSceneWithShadow(void (*fpDraw)(void*), void* func_obj)
	{
		float light_proj[16], camera_proj[16];
		float light_modelview[16], camera_modelview[16];


		//
		// ���݂̎��_�s��C�����s����擾 or �쐬
		//
		glMatrixMode(GL_PROJECTION);

		// ���_�v���W�F�N�V�����s��̎擾
		glGetFloatv(GL_PROJECTION_MATRIX, camera_proj);
		glPushMatrix();	// ���̃v���W�F�N�V�����s���ޔ������Ă���


		glMatrixMode(GL_MODELVIEW);
		// ���_���f���r���[�s��̎擾
		glGetFloatv(GL_MODELVIEW_MATRIX, camera_modelview);
		glPushMatrix();	// ���̃��f���r���[�s���ޔ������Ă���



		// �ޔ������Ă��������_�s������ɖ߂�
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();


		//
		// �J�������猩���Ƃ��̃V�[���`��F�e�̈�
		// 
		glClear(GL_DEPTH_BUFFER_BIT);

		// �e�G���A�p�̈Â����C�g�̐ݒ�(�Ȃ�ׂ����̌����ݒ�Əd�����Ȃ��悤��LIGHT7���g�p)
//		float light_pos[4] = { light.Origin.mX, light.Origin.mY, light.Origin.mZ, 1.0 };
		float light_pos[4] = { 10,7000,10, 1.0 };
		glLightfv(GL_LIGHT7, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT7, GL_AMBIENT, RX_LIGHT_DIM);
		glLightfv(GL_LIGHT7, GL_DIFFUSE, RX_LIGHT_DIM);
		glLightfv(GL_LIGHT7, GL_SPECULAR, RX_LIGHT_BLACK);
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT7);
		glEnable(GL_LIGHTING);

		// �`��
		fpDraw(func_obj);

		glDisable(GL_LIGHT7);


		//
		// �J�������猩���Ƃ��̃V�[���`��F�����̈�
		// 
		glEnable(GL_LIGHT0);

		// �e�N�X�`���s��p�̃o�C�A�X�s��		
		const float bias[16] = { 0.5, 0.0, 0.0, 0.0,
								 0.0, 0.5, 0.0, 0.0,
								 0.0, 0.0, 0.5, 0.0,
								 0.5, 0.5, 0.5, 1.0 };

		// �e�N�X�`���s��(���_��Ԃ��烉�C�g��Ԃւ̕ϊ��s��)�̌v�Z
		float tex_mat[16], tmp[16];
		MulMat(tmp, bias, light_proj);
		MulMat(tex_mat, tmp, light_modelview);

		// �e�N�X�`�����W�n�̐ݒ�
		float t[4];
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		t[0] = tex_mat[0]; t[1] = tex_mat[4]; t[2] = tex_mat[8]; t[3] = tex_mat[12];
		glTexGenfv(GL_S, GL_EYE_PLANE, t);
		glEnable(GL_TEXTURE_GEN_S);

		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		t[0] = tex_mat[1]; t[1] = tex_mat[5]; t[2] = tex_mat[9]; t[3] = tex_mat[13];
		glTexGenfv(GL_T, GL_EYE_PLANE, t);
		glEnable(GL_TEXTURE_GEN_T);

		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		t[0] = tex_mat[2]; t[1] = tex_mat[6]; t[2] = tex_mat[10]; t[3] = tex_mat[14];
		glTexGenfv(GL_R, GL_EYE_PLANE, t);
		glEnable(GL_TEXTURE_GEN_R);

		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		t[0] = tex_mat[3]; t[1] = tex_mat[7]; t[2] = tex_mat[11]; t[3] = tex_mat[15];
		glTexGenfv(GL_Q, GL_EYE_PLANE, t);
		glEnable(GL_TEXTURE_GEN_Q);


		// �V���h�E�}�b�v�e�N�X�`��
		glBindTexture(GL_TEXTURE_2D, m_iTexShadowMap);
		glEnable(GL_TEXTURE_2D);

		// �e�N�X�`��R���W�ƃe�N�X�`�����r����悤�ɐݒ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

		// R <= �e�N�X�`���̒l �Ȃ��true(����)�ɂ���
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

		// ��r���ʂ͑S�̂̐F�Ƃ��Ĕ��f(�A���t�@�l����(GL_ALPHA)�ł��悢)
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

		// ���l�̔�r�֐���ݒ�(��2�����͂������l)
		glAlphaFunc(GL_GEQUAL, 0.5f);
		glEnable(GL_ALPHA_TEST);

		// �������������̐}�`�ɏd�˂ď������悤�Ƀf�v�X��r�֐���ݒ�
		glDepthFunc(GL_LEQUAL);

		fpDraw(func_obj);

		glDisable(GL_TEXTURE_2D);

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_GEN_Q);

		glDisable(GL_LIGHTING);
		glDisable(GL_ALPHA_TEST);
	}


	/*!
	 * �f�v�X�}�b�v���e�N�X�`���Ƃ��ĕ\��
	 * @param[in] w,h �E�B���h�E�T�C�Y
	 */
	void DrawDepthTex(int w, int h)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, w, 0, h, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glDisable(GL_LIGHTING);
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, m_iTexShadowMap);
		glEnable(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

		glNormal3d(0, 0, -1);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3f(0.05 * w, 0.05 * h, 0);
		glTexCoord2d(1, 0); glVertex3f(0.05 * w + 100, 0.05 * h, 0);
		glTexCoord2d(1, 1); glVertex3f(0.05 * w + 100, 0.05 * h + 100, 0);
		glTexCoord2d(0, 1); glVertex3f(0.05 * w, 0.05 * h + 100, 0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
};


/*!
 * ������̐���
 * @param[in] fov_deg ����p[deg]
 * @param[in] near_d,far_d ���������͈̔�
 * @param[in] w,h �E�B���h�E�T�C�Y
 * @param[in] pos ���_�ʒu
 * @param[in] lookat �����_�ʒu
 * @param[in] up �����
 * @return ������
 */
inline rxFrustum CalFrustum(double fov_deg, double near_d, double far_d, int w, int h,
	Vec3 pos, Vec3 lookat = Vec3(), Vec3 up = Vec3(0.0, 1.0, 0.0))
{
	rxFrustum f;
	f.Near = near_d;
	f.Far = far_d;
	f.FOV = fov_deg;
	f.W = w;
	f.H = h;
	f.Origin = pos;
	f.LookAt = lookat;
	f.Up = up;
	return f;
}

/*!
	* �v���W�F�N�V�����s��C���_�ʒu�̐ݒ�
	* @param[in] f ������
	*/
inline void SetFrustum(const rxFrustum& f)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(f.FOV, (double)f.W / (double)f.H, f.Near, f.Far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(f.Origin.mX, f.Origin.mY, f.Origin.mZ, f.LookAt.mX, f.LookAt.mY, f.LookAt.mZ, f.Up.mX, f.Up.mY, f.Up.mZ);
}




#endif // #ifdef _RX_SHADOWMAP_H_