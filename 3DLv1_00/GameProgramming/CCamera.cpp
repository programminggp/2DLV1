#include "CCamera.h"
#include "glut.h"

CCamera::CCamera()
: mUp(0.0f, 1.0f, 0.0f)
, mEye(10.0f, 10.0f, 10.0f)
, mCenter(0.0f, 0.0f, 0.0f)
{

}

void CCamera::Render() {
	gluLookAt(mEye.mX, mEye.mY, mEye.mZ, mCenter.mX, mCenter.mY, mCenter.mZ, mUp.mX, mUp.mY, mUp.mZ);
}
