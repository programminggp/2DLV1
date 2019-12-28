#include "CCamera.h"
#include "glut.h"

void CCamera::Camera2D() {
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
	gluOrtho2D(mX - mW, mX + mW, mY - mH, mY + mH);	//2Dの画面を設定
	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化
}

void CCamera::Camera2D(float x, float y, float w, float h) {
	mX = x;
	mY = y;
	mW = w;
	mH = h;
	Camera2D();
}
