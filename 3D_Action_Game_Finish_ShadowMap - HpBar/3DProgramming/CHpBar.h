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


		//行列をプロジェクションモードへ変更
		glMatrixMode(GL_PROJECTION);
		//現在のプロジェクション行列を退避
		glPushMatrix();
		//行列を初期化
		glLoadIdentity();

		//2D画面表示領域を設定
		//画面の左座標，画面の右座標，画面の下座標，画面の上座標
		gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);	//2Dの画面座標を設定

		//行列をモデルビューモードへ変更
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//行列を初期化
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

		//退避した行列に戻す
		glPopMatrix();

		//行列をプロジェクションモードへ変更
		glMatrixMode(GL_PROJECTION);
		//退避した行列に戻す
		glPopMatrix();

		//行列をモデルビューモードへ変更
		glMatrixMode(GL_MODELVIEW);
	};
};

#endif
