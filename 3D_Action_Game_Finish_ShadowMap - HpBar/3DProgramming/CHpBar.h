#ifndef CHPBAR_H
#define CHPBAR_H

#include "main.h"

extern CVector3 WorldToViewportPoint(const CVector3 &vector);

class CHPBar {
	CVector2 mScale;
	float mMax;
public:
	CVector3 mPosition;
	float mValue;
	CHPBar(const CVector3 &position, const CVector2 &scale, float max, float value) {
		mPosition = position;
		mScale = scale;
		mMax = max;
		mValue = value;
	};

	void SetPosition(const CVector3 &v) {
		mPosition = WorldToViewportPoint(v);
	}

	void Render() {
		if (mPosition.z < 0.0f) return;
		if (mValue < 0.0f) mValue = 0.0f;
		if (mValue > mMax) mValue = mMax;
		float left = mPosition.x - mScale.x;
		float right = left + (mScale.x * 2) * mValue / mMax;
		float top = mPosition.y + mScale.y;
		float bot = mPosition.y - mScale.y;


		//�s����v���W�F�N�V�������[�h�֕ύX
		glMatrixMode(GL_PROJECTION);
		//���݂̃v���W�F�N�V�����s���ޔ�
		glPushMatrix();
		//�s���������
		glLoadIdentity();

		//2D��ʕ\���̈��ݒ�
		//��ʂ̍����W�C��ʂ̉E���W�C��ʂ̉����W�C��ʂ̏���W
		gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);	//2D�̉�ʍ��W��ݒ�

		//�s������f���r���[���[�h�֕ύX
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//�s���������
		glLoadIdentity();

		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glBegin(GL_QUADS);
		glVertex2f(left, top);
		glVertex2f(left, bot);
		glVertex2f(right, bot);
		glVertex2f(right, top);
		glEnd();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		//�ޔ������s��ɖ߂�
		glPopMatrix();

		//�s����v���W�F�N�V�������[�h�֕ύX
		glMatrixMode(GL_PROJECTION);
		//�ޔ������s��ɖ߂�
		glPopMatrix();

		//�s������f���r���[���[�h�֕ύX
		glMatrixMode(GL_MODELVIEW);
	};
};

#endif
