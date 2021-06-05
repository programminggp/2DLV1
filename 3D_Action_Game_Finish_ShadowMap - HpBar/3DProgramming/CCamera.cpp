#include "Windows.h"
#include "glut.h"
#include "CCamera.h"
#include "CMatrix44.h"

//38
CMatrix44 CCamera::mCameraInverse;
extern CMatrix44 GMatrixModelView;

//�J�����̏�����̏�����
CCamera::CCamera() : mUp(0.0f, 1.0f, 0.0f) {
	//���_�ƒ����_�̐ݒ�
//	setPos(0.0f, 0.0f, 0.0f);
}

/* ���_�ƒ����_�̐ݒ�
void setPos(float x, float y, float z)
x:�����_��X���W y:�����_��Y���W z:�����_��Z���W
�K��̎��_�͒����_���Y��+2�AZ��+4�ړ�
*/
void CCamera::setPos(float x, float y, float z) {
	//�����_�̐ݒ�
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	//���_�̐ݒ�
	eye[0] = pos[0];
	eye[1] = pos[1] + 1.0f;
	eye[2] = pos[2] + 10.0f;
	//�J�����s��̐ݒ�
	gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], 0.0f, 1.0f, 0.0f);
}

/* �X�V����
�L�[�ɂ�莋�_��ύX����
J�F���O����@K�F�O�ʂ���@L�F�E�O����
U�F����납��@I�F��납��@O�F�E��납��
*/
void CCamera::update() {
	//�s��̃��[�h�����f���r���[�ɂ���
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�̍s���P�ʍs��ɂ���
	glLoadIdentity();
	//���_�̐ݒ�
	gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], mUp.x, mUp.y, mUp.z);
	//�J�����̍s����擾
	glGetFloatv(GL_MODELVIEW_MATRIX, GMatrixModelView.f);
	//�J�����̋t�s����擾
	mCameraInverse = GMatrixModelView.getInverse();
	//�ړ��̗v�f���폜
	mCameraInverse.m[3][0] = mCameraInverse.m[3][1] = mCameraInverse.m[3][2] = 0.0f;
	//	update(CVector3(eye[0], eye[1], eye[2]), CVector3(pos[0], pos[1], pos[2]), CVector3(mUp.x, mUp.y, mUp.z));
}
//35
//�J�����s��̐ݒ�
void CCamera::update(CVector3 aeye, CVector3 pos, CVector3 up) {
	//�s��̃��[�h�����f���r���[�ɂ���
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�̍s���P�ʍs��ɂ���
	glLoadIdentity();
	//���_�̐ݒ�
	gluLookAt(aeye.x, aeye.y, aeye.z, pos.x, pos.y, pos.z, up.x, up.y, up.z);
	//�J�����̍s����擾
	glGetFloatv(GL_MODELVIEW_MATRIX, GMatrixModelView.f);
	//�J�����̋t�s����擾
	mCameraInverse = GMatrixModelView.getInverse();
	//�ړ��̗v�f���폜
	mCameraInverse.m[3][0] = mCameraInverse.m[3][1] = mCameraInverse.m[3][2] = 0.0f;

}
