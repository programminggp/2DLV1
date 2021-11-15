#include "CCamera.h"
#include "glut.h"

//カメラの外部変数
CCamera Camera;

void CCamera::Set(const CVector &eye, const CVector &center, const CVector &up) {
	mEye = eye;
	mCenter = center;
	mUp = up;
}

void CCamera::Render() {
	/* モデルビュー変換行列に戻す */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(mEye.mX, mEye.mY, mEye.mZ, mCenter.mX, mCenter.mY, mCenter.mZ, mUp.mX, mUp.mY, mUp.mZ);
}
