#include "CCamera.h"
#include "glut.h"

//ƒJƒƒ‰‚ÌŠO•”•Ï”
CCamera Camera;

void CCamera::Set(const CVector& eye, const CVector& center, const CVector& up) {
	mEye = eye;
	mCenter = center;
	mUp = up;
}

void CCamera::Render() {
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(), mCenter.X(), mCenter.Y(), mCenter.Z(), mUp.X(), mUp.Y(), mUp.Z());
}

const CVector& CCamera::Eye() const {
	return CCamera::mEye;
}