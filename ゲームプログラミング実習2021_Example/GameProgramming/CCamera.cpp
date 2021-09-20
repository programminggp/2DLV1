#include "CCamera.h"
#include "glut.h"

//ƒJƒƒ‰‚ÌŠO•”•Ï”
CCamera Camera;

void CCamera::Set(const CVector &eye, const CVector &center,
	const CVector &up) {
	mEye = eye;
	mCenter = center;
	mUp = up;
}

void CCamera::Render() {
	gluLookAt(mEye.mX, mEye.mY, mEye.mZ,
		mCenter.mX, mCenter.mY, mCenter.mZ,
		mUp.mX, mUp.mY, mUp.mZ);
}
